#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv, char *envp)
{
	while(1)
	{
		const pid_t pid = fork();
	if (pid < 0) {
		printf("fork error\n");
		return -1;
		}
	if (pid) {
		int status;
		waitpid(pid, &status, 0);
		write(stdout, WEXITSTATUS(status), sizeof(int));
		} else {
			char path[255], args[4096], pathargs[4096];
			int i;
			for(i = 0; i < 255; i++)
				args[i] = path[i] = 0;
			for(i = 255; i < 4096; i++)
				args[i] = 0;
			scanf("%s", pathargs);
			i = 0;
			while(pathargs[i] != ' ') {
				path[i] = pathargs[i];
				i++;
			}
			i++;
			int j = 0;
			while(pathargs[i]) {
				args[j] = pathargs[i];
				i++;
				j++;
			}
			execvp(path, args);
			printf("exec error\n");
			return -1;
		}
	}
	return 0;
}
