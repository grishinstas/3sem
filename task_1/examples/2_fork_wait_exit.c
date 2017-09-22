#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv, char *envp)
{
	const pid_t pid = fork();
	if (pid < 0) {
		printf("fork() error\n");
		return -1;
	}
	if (pid) {
		int status;
		waitpid(pid, &status, 0);
		printf("Ret code: %d\n", WEXITSTATUS(status));
	} else {
		execl(*argv, 0);
	}
	return 0;
}
