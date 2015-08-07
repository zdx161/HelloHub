#define UNW_LOCAL_ONLY
#include <libunwind.h>
#include <stdio.h>
#include <stdlib.h>

void show_backtrace (void) {
    unw_cursor_t cursor; unw_context_t uc;
    unw_word_t ip, sp;

    unw_getcontext(&uc);
    unw_init_local(&cursor, &uc);
    char buf[512] ={0};

    while (unw_step(&cursor) > 0) {
        unw_get_reg(&cursor, UNW_REG_IP, &ip);
        unw_get_proc_name(&cursor,buf,sizeof(buf), &ip);
        printf("proc name:%s\n", buf);
        unw_get_reg(&cursor, UNW_REG_SP, &sp);
        printf ("ip = %lx, sp = %lx\n", (long) ip, (long) sp);
    }
}

void show(){

    show_backtrace();
}

int main()
{
    //show_backtrace();
    show();

    return 0;
}
