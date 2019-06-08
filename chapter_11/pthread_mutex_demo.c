#include<unistd.h>
#include<time.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main()
{
    int err;
    struct timespec tout;
    struct tm *tmp;
    char buf[64];

    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&lock);
    printf("mutex is locked\n");
    clock_gettime(CLOCK_REALTIME,&tout);
    tmp = localtime(&tout.tv_sec);
    strftime(buf,sizeof(buf),"%r",tmp);
    printf("current time is %s \n",buf);

    tout.tv_sec += 2;

    err = pthread_mutex_timedlock(&lock,&tout);
    clock_gettime(CLOCK_REALTIME, &tout);
    strftime(buf, sizeof(buf), "%r", tmp);
    printf("now time is %s \n", buf);

    if(err == 0)
    {
        printf("mutex is locked again!\n");
    }
    else
    {
        errno = err;
        perror("can't lock mutex again");
    }
    exit(0);
}