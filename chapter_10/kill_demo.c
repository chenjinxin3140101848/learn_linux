#include<unistd.h>
#include<stdio.h>
#include<signal.h>

void myhandle(int signo)
{
    printf("myhandle signo = %d\n", signo);
}
int main(void)
{
    int pid = 0;
    int iret = 0;
    signal(SIGALRM,myhandle);
    signal(SIGCHLD, myhandle);
    sleep(1);
    
    raise(SIGALRM); /*equals kill(getpid(),SIGALRM)*/

    pid = getpid();
    /*if pid >0,it sends signal to the process  whose pid equals pid.
     *if pid = 0,it sends signal to all processes this process has right to send signal in the same process group  .
     *if pid < 0,it sends signal to the process group whose pid equals |pid| while this process has right to send signal to .
     if pid = -1,it sends signal to all the process which this process has right to send signal to .
     */
    /*signal SIGCHLD is not blocked,the signal send to the process brfore the function return*/
    iret = kill(pid, SIGCHLD);
    printf("call kill return value iret = %d.\n",iret);
    
    return 0;
}
/*
result printed:
myhandle signo = 14
myhandle signo = 17
call kill return value iret = 0.
*/