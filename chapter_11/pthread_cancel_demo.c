#include<unistd.h>
#include<pthread.h>

int main()
{
    //todo
    pthread_cancel(pthread_self());
    return 0;
}