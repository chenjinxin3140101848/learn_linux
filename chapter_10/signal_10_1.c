#include<signal.h>
#include<stdio.h>
#include<unistd.h>
#define MAXLEN  100

void myhandle(int sig)
{
    printf("receive signal == %d\n", sig);
    return;
}
int main(int argc,char * arg[])
{
    char buf[MAXLEN] = {0};
    getcwd(buf, MAXLEN);
    printf("__FILE__ = %s/%s,line == %d\r\n", buf, __FILE__,__LINE__);
    signal(SIGUSR1, myhandle);
    for(;;)
    {
        pause();
    }
    return 0;
}