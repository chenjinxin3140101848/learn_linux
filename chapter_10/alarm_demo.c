#include<unistd.h>
#include<signal.h>
#include<setjmp.h>
#include<apue.h>
static void sig_alarm(int signo)
{
    //todo nothing,just return to wake up the pause.
}
/*this function has several defects,needs to be optimized ,see as sleep2*/
unsigned int sleep1(unsigned int second)
{
    if(signal(SIGALRM,sig_alarm) == SIG_ERR)
    {
        return second;
    }
    alarm(second);
    pause();
    return alarm(0);
}

static jmp_buf env_alrm;

static void sig_alrm2(int signo)
{
    longjmp(env_alrm,1);
}

/*this function may termidate other interrupt hanlders earlier than expected*/
unsigned int sleep2(unsigned int second)
{
    if (signal(SIGALRM, sig_alrm2) == SIG_ERR)
    {
        return second;
    }
    /*set global jump .in sleep2,setjmp return 0,after sig_alrm2 called,setjmp return 1 which return from the second param of longjmp
      it avoid the abnormal situation when the SIGALRM caught before pause().
    */
    if (setjmp(env_alrm) == 0)
    {
        alarm(second);
        pause();
    }
    return (alarm(0));
       
    
    

}

static void sig_int(int signo);
int main(void)
{
    unsigned int unslept = 0;
    if(signal(SIGINT,sig_int) == SIG_ERR)
    {
        err_sys("signal(SIGINT) error\n");
    }
    unslept = sleep2(5);
    printf("sleep2 returned:%u\n",unslept);
    exit(0);
}

static void sig_int(int signo)
{
    int i,j;
    volatile int k;
    printf("\nsig_int starting\n");
    for(i = 0;i < 300000;i++)
        for(j = 0;j < 40000;j++)
            k += i*j;
    printf("sig_int finished.\n");
    return;
}