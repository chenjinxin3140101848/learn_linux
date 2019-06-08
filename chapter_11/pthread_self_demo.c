/*to compile ,run :gcc pthread_self_demo.c -o pthread_self_demo -pthread*/
#include<unistd.h>
#include<apue.h>
#include<stdio.h>
#include<pthread.h>
void *printids(void *args)
{
	pthread_t tid = pthread_self();
	printf("self thread id is %d.\n", tid);
	return 0;
}

int main()
{
	pthread_t tid = 0;
	pthread_create(&tid, NULL, printids, NULL);
	sleep(1);
	printids(NULL);
}
