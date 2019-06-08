#include<signal.h>
#include<unistd.h>

int main(void)
{
  sigset_t newmask;
  sigemptyset(&newmask);
  sigprocmask(SIG_BLOCK,&newmask,NULL);
  return 0;
}
