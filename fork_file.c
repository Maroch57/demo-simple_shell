#include <stdio.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;
	pid_t ppid;

	/*written before fork was called */

	/*called fork */
	//printf("Before fork I was one\n");

	pid = fork();

	if (pid == -1)
	{
		perror("Unsuccessful\n");
		return 1;
	}

	//printf("After fork I became two\n");

	if (pid == 0)
	{
		sleep(40);
		printf("I am the child\n");
	}
	else
		ppid = getppid();
		printf("Parent pid is: %u\n", ppid);

	return (0);
}
