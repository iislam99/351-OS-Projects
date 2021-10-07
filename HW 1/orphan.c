/*
Iftekharul Islam (893441071)
Due: 11 Sept. 2020
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


/**
 * The function to be executed by the child
 */
void child()
{

	/** NOTE: getpid() returns the process id of the caller process **/
	fprintf(stderr, "Hi! I am the child. My pid is %d. I am immortal!\n", getpid());

	exit(0);

	if(execlp("yes", "yes", NULL) < 0)
	{
		perror("execlp");
		exit(-1);
	}

}

int main(int argc, char** argv)
{
	/* The process id of the child */
	pid_t child_pid;

	/* If the fork failed, then terminate. Otherwise, save the
	 * value returned by fork().
	 */
	if((child_pid = fork()) < 0)
	{
		perror("fork");
		exit(-1);
	}

	/* Are we a child process ? */
	if(child_pid == 0)
	{
		fprintf(stderr, "I am the child and my pid is %d\n\n", getpid());

		/* Call the child function */
		child();
	}
	/* We are the parent */
	else
	{
		fprintf(stderr, "Hi! I am a parent. Just created a child with pid %d\n", child_pid);
		fprintf(stderr, "I will live for 60 seconds. My child shall live forever!\n");

		fprintf(stderr, "\nI am the parent and my pid is %d\n", getpid());

		/* Wait for 60 seconds, then die. NEVER CALL WAIT */
		sleep(60);

		exit(0);

	}
	return 0;
}
