#include <unistd.h>
#include<signal.h>
#include <asm-generic/signal-defs.h>
#include<apue.h>
/*保护临界区,使其不被指定的信号中断的正确方法*/
static void sig_int(int);
int main()
{
    __sigset_t newmask, oldmask, zeromask;
    if(signal(SIGINT,sig_int) == SIG_ERR)
    {
        err_sys("signal(SIGINT) error!");
    }

    sigemptyset(&newmask);
    sigemptyset(&zeromask);
    sigaddset(&newmask,SIGINT);

    if(sigprocmask(SIG_SETMASK,&newmask,&oldmask) < 0)
    {
        err_sys("SIG_BLOCK error!");
    }
    

    
}

static void sig_int(int signo)
{
    pr_mask("\nin sig_int: ");
}




