from pylab import *

ax = gca()
ax.spines['right'].set_color('none')
ax.spines['top'].set_color('none')
ax.xaxis.set_ticks_position('bottom')
ax.spines['bottom'].set_position(('data',0))
ax.yaxis.set_ticks_position('left')
ax.spines['left'].set_position(('data',0))

db = np.linspace(-56.0, 0, 16, endpoint = True)
amp = exp(db * 0.115129)
ax.plot(db, amp)

fig = figure()
plot(db, amp * 4096, linestyle = "-", label = "4096")
plot(db, amp * 2048, linestyle = "-", label = "2048")
plot(db, amp * 1024, linestyle = "-", label = "1024")
plot(db, amp * 8192, linestyle = "-", label = "8192")
legend(loc = 'upper left')

figure()
plot(db, amp * 32767)

show()
