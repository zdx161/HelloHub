#include <sys/socket.h>


/*****************************************************************************
**
**   bluedroid stack adaptation
**
*****************************************************************************/

static int skt_connect(struct a2dp_stream_out *out, char *path)
{
    int ret;
    int skt_fd;
    struct sockaddr_un remote;
    int len;

    INFO("connect to %s (sz %d)", path, out->buffer_sz);

    skt_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if(skt_fd == -1)
    {
        return -1;
    }


    if(socket_local_client_connect(skt_fd, path,
            ANDROID_SOCKET_NAMESPACE_ABSTRACT, SOCK_STREAM) < 0)
    {
        ERROR("failed to connect (%s)", strerror(errno));
        close(skt_fd);
        return -1;
    }

    len = out->buffer_sz;
    ret = setsockopt(skt_fd, SOL_SOCKET, SO_SNDBUF, (char*)&len, (int)sizeof(len));

    /* only issue warning if failed */
    if (ret < 0)
        ERROR("setsockopt failed (%s)", strerror(errno));

    INFO("connected to stack fd = %d", skt_fd);

    return skt_fd;
}

static int skt_write(int fd, const void *p, size_t len)
{
    int sent;
    struct pollfd pfd;

    FNLOG();

    pfd.fd = fd;
    pfd.events = POLLOUT;

    /* poll for 500 ms */

    /* send time out */
    if (poll(&pfd, 1, 500) == 0)
        return 0;

    ts_log("skt_write", len, NULL);

    if ((sent = send(fd, p, len, MSG_NOSIGNAL)) == -1)
    {
        ERROR("write failed with errno=%d\n", errno);
        return -1;
    }

    return sent;
}

static int skt_disconnect(int fd)
{
    INFO("fd %d", fd);

    if (fd != AUDIO_SKT_DISCONNECTED)
    {
        shutdown(fd, SHUT_RDWR);
        close(fd);
    }
    return 0;
}



/*****************************************************************************
**
**  AUDIO CONTROL PATH
**
*****************************************************************************/

static int a2dp_command(struct a2dp_stream_out *out, char cmd)
{
    char ack;
    int ret_s = 0, ret_r = 0;

    DEBUG("A2DP COMMAND %s", dump_a2dp_ctrl_event(cmd));

    /* send command */
    if ((ret_s = send(out->ctrl_fd, &cmd, 1, MSG_NOSIGNAL)) == -1)
    {
        ERROR("cmd failed (%s)", strerror(errno));
        skt_disconnect(out->ctrl_fd);
        out->ctrl_fd = AUDIO_SKT_DISCONNECTED;
        return -1;
    }

    /* wait for ack byte */
    if ((ret_r = recv(out->ctrl_fd, &ack, 1, MSG_WAITALL | MSG_NOSIGNAL)) < 0)
    {
        ERROR("ack failed (%s), ret_s: %d, ret_r: %d", strerror(errno), ret_s, ret_r);
        #ifndef HAS_BLUETOOTH_SPRD
        skt_disconnect(out->ctrl_fd);
        out->ctrl_fd = AUDIO_SKT_DISCONNECTED;
        #endif
        return -1;
    }

    DEBUG("A2DP COMMAND %s DONE STATUS %d", dump_a2dp_ctrl_event(cmd), ack);

    if (ack != A2DP_CTRL_ACK_SUCCESS)
        return -1;

    return 0;
}

/*****************************************************************************
**
** AUDIO DATA PATH
**
*****************************************************************************/

static void a2dp_stream_out_init(struct a2dp_stream_out *out)
{
    pthread_mutexattr_t lock_attr;

    FNLOG();

    pthread_mutexattr_init(&lock_attr);
    pthread_mutexattr_settype(&lock_attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&out->lock, &lock_attr);

    out->ctrl_fd = AUDIO_SKT_DISCONNECTED;
    out->audio_fd = AUDIO_SKT_DISCONNECTED;
    out->state = AUDIO_A2DP_STATE_STOPPED;

    out->cfg.channel_flags = AUDIO_STREAM_DEFAULT_CHANNEL_FLAG;
    out->cfg.format = AUDIO_STREAM_DEFAULT_FORMAT;
    out->cfg.rate = AUDIO_STREAM_DEFAULT_RATE;

    /* manages max capacity of socket pipe */
    out->buffer_sz = AUDIO_STREAM_OUTPUT_BUFFER_SZ;
}

static int start_audio_datapath(struct a2dp_stream_out *out)
{
    int oldstate = out->state;

    INFO("state %d", out->state);

    if (out->ctrl_fd == AUDIO_SKT_DISCONNECTED)
        return -1;

    out->state = AUDIO_A2DP_STATE_STARTING;

    if (a2dp_command(out, A2DP_CTRL_CMD_START) < 0)
    {
        ERROR("audiopath start failed");

        out->state = oldstate;
        return -1;
    }

    /* connect socket if not yet connected */
    if (out->audio_fd == AUDIO_SKT_DISCONNECTED)
    {
        out->audio_fd = skt_connect(out, A2DP_DATA_PATH);

        if (out->audio_fd < 0)
        {
            out->state = oldstate;
            return -1;
        }

        out->state = AUDIO_A2DP_STATE_STARTED;
    }

    return 0;
}


static int stop_audio_datapath(struct a2dp_stream_out *out)
{
    int oldstate = out->state;

    INFO("state %d", out->state);

    if (out->ctrl_fd == AUDIO_SKT_DISCONNECTED)
         return -1;

    /* prevent any stray output writes from autostarting the stream
       while stopping audiopath */
    out->state = AUDIO_A2DP_STATE_STOPPING;

    if (a2dp_command(out, A2DP_CTRL_CMD_STOP) < 0)
    {
        ERROR("audiopath stop failed");
        out->state = oldstate;
        return -1;
    }

    out->state = AUDIO_A2DP_STATE_STOPPED;

    /* disconnect audio path */
    skt_disconnect(out->audio_fd);
    out->audio_fd = AUDIO_SKT_DISCONNECTED;

    return 0;
}

static int suspend_audio_datapath(struct a2dp_stream_out *out, bool standby)
{
    INFO("state %d", out->state);

    if (out->ctrl_fd == AUDIO_SKT_DISCONNECTED)
         return -1;

    if (out->state == AUDIO_A2DP_STATE_STOPPING)
        return -1;

    if (a2dp_command(out, A2DP_CTRL_CMD_SUSPEND) < 0)
        return -1;

    if (standby)
        out->state = AUDIO_A2DP_STATE_STANDBY;
    else
        out->state = AUDIO_A2DP_STATE_SUSPENDED;

    /* disconnect audio path */
    skt_disconnect(out->audio_fd);

    out->audio_fd = AUDIO_SKT_DISCONNECTED;

    return 0;
}

static int check_a2dp_ready(struct a2dp_stream_out *out)
{
    INFO("state %d", out->state);

    if (a2dp_command(out, A2DP_CTRL_CMD_CHECK_READY) < 0)
    {
        ERROR("check a2dp ready failed");
        return -1;
    }
    return 0;
}


/*****************************************************************************
**
**  audio output callbacks
**
*****************************************************************************/

static ssize_t out_write(struct audio_stream_out *stream, const void* buffer,
                         size_t bytes)
{
    struct a2dp_stream_out *out = (struct a2dp_stream_out *)stream;
    int sent;

    DEBUG("write %d bytes (fd %d)", bytes, out->audio_fd);

    if (out->state == AUDIO_A2DP_STATE_SUSPENDED)
    {
        DEBUG("stream suspended");
        return -1;
    }

    /* only allow autostarting if we are in stopped or standby */
    if ((out->state == AUDIO_A2DP_STATE_STOPPED) ||
        (out->state == AUDIO_A2DP_STATE_STANDBY))
    {
        pthread_mutex_lock(&out->lock);

        if (start_audio_datapath(out) < 0)
        {
            /* emulate time this write represents to avoid very fast write
               failures during transition periods or remote suspend */

            int us_delay = calc_audiotime(out->cfg, bytes);

            INFO("emulate a2dp write delay (%d us)", us_delay);

            usleep(us_delay);
            pthread_mutex_unlock(&out->lock);
            usleep(50*1000);
            return -1;
        }

        pthread_mutex_unlock(&out->lock);
    }
    else if (out->state != AUDIO_A2DP_STATE_STARTED)
    {
        ERROR("stream not in stopped or standby");
        return -1;
    }

    sent = skt_write(out->audio_fd, buffer,  bytes);

    if (sent == -1)
    {
        skt_disconnect(out->audio_fd);
        out->audio_fd = AUDIO_SKT_DISCONNECTED;
        out->state = AUDIO_A2DP_STATE_STOPPED;
    }

    DEBUG("wrote %d bytes out of %d bytes", sent, bytes);
    return sent;
}

/************************************************************
 **
 **
 **   call functions to implement communication
 **
 ***********************************************************/

a2dp_stream_out_init(out);

skt_connect(out, A2DP_CTRL_PATH);

check_a2dp_ready(out);

skt_disconnect(out->ctrl_fd);

setsockopt();


