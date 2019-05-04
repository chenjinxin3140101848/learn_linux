/*对于早期linux内核，该程序逻辑有问题。如果将SIGCLD的配置设置为捕捉，则内核会立即检查是否有子进程准备好被等待（父进程调用wait(1)）,如果是这样，则调用SIGCLD处理函数。
 *但是linx3.2.0以后当一个进程安排捕捉SIGCHLD(与SIGCLD的值相同)，并且已经有进程准备好由其父进程等待时，该系统并不调用SIGCHLD信号的处理函数。
 */
#include	"apue.h"
#include	<sys/wait.h>

static void	sig_cld(int);

int
main()
{
	pid_t	pid;

	if (signal(SIGCLD, sig_cld) == SIG_ERR)
		perror("signal error");
	if ((pid = fork()) < 0) {
		perror("fork error");
	} else if (pid == 0) {		/* child */
		printf("child pid = %d\n",getpid());
		sleep(2);
		_exit(0);
	}
	printf("parent pid = %d\n", getpid());
	pause();	/* parent */
	exit(0);
}

static void
sig_cld(int signo)	/* interrupts pause() */
{
	pid_t	pid;
	int		status;

	printf("SIGCLD received and current pid = %d\n",getpid());

	if (signal(SIGCLD, sig_cld) == SIG_ERR)	/* reestablish handler */
		perror("signal error");

	if ((pid = wait(&status)) < 0)		/* fetch child status */
		perror("wait error");

	printf("child pid = %d\n", pid);
}
