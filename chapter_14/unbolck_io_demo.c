#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<apue.h>
char buf[100000];

int main(void)
{
    int ntowrite,nwrite;
    char *ptr = NULL;
    
    ntowrite = read(STDIN_FILENO,buf,sizeof(buf));
    fprintf(stderr,"read %d bytes \n",ntowrite);
    
    int val = 0;
    if((val = fcntl(STDOUT_FILENO,F_GETFL,0)) < 0)
    {
        err_sys("fcntl F_GETFL error");
    }
    val |= O_NONBLOCK;
    if(fcntl(STDOUT_FILENO,F_SETFL,val) < 0)
    {
        err_sys("fcntl F_SETFL error");
    }

    for(ptr = buf;ntowrite > 0;)
    {
        errno = 0;
        nwrite = write(STDOUT_FILENO,ptr,ntowrite);
        fprintf(stderr,"nwrite = %d,error = %d\n",nwrite,errno);
        if(nwrite > 0)
	{
	     ptr += nwrite;
	     ntowrite -= nwrite; 
	}
    }
    if((val = fcntl(STDOUT_FILENO,F_GETFL,0)) < 0)
    {
        err_sys("fcntl F_GETFL error");
    }
    val ^=  O_NONBLOCK;
    if(fcntl(STDOUT_FILENO,F_SETFL,val) < 0)
    {
        err_sys("fcntl F_SETFL error");
    }
    return 0;
    
}
