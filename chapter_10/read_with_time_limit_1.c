#include<apue.h>

static void sig_alrm(int signo);

int main(void)
{
    int n = 0;
    char line[MAXLINE];
    if(signal(SIGALRM,sig_alrm) == SIG_ERR)
    {
        err_sys("signal(SIGALRM) error.");
    }
    alarm(10);
    if(n = read(STDIN_FILENO,line,MAXLINE) < 0)
    {
        err_sys("read error\n");
    }
    alarm(0);

    write(STDOUT_FILENO,line,n);
    exit(0);
}

static void sig_alrm(int signo)
{
    //to do nothing,just return to interupt the read.
}