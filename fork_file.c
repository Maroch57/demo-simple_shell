#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
	pid_t pid;
	//pid_t ppid;

	/*written before fork was called */
	//printf("Before fork I was one\n");
	
	/* child process is created */
	pid = fork();

	/* if  fork fails */
	if (pid == -1)
	{
		perror("Unsuccessful\n");
		return 1;
	}

	//printf("After fork I became two\n");

	/* in child process */
	if (pid == 0)
	{
		//sleep(40);
		printf("I am the child process\n");
	}
	/* in parent process */
	else
	{
		//ppid = getppid();
		wait(NULL);
		sleep(30);
		printf("Parent process\n");
	}

	return (0);
}
