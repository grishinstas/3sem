#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	char buf[4096];
	int fd[2];
	int pd[2];
	int p;
	p = pipe(fd);
	if (p < 0) {
		printf("pipe error");
		exit(-1);
	}
	p = pipe(pd);
	if (p < 0) {
		printf("pipe error");
		exit(-1);
	}
	p = fork();
	if (p < 0) {
		printf("fork error");
		exit(-1);
	}
	if (p) {
		int i;
		while((read(fd[0], buf, sizeof(buf))) > 0) {
			printf("received: %s\n", buf);
			for(i = 0; i < sizeof(buf); i++)
				buf[i] = '\0';
			scanf("%s", buf);
			printf("sent: %s\n", buf);
			write(pd[1], buf, sizeof(buf));
		}
		close(fd[0]);
		close(pd[1]);
		exit(0);
	} else {
		int i;
		while((read(pd[0], buf, sizeof(buf))) > 0) {
			printf("received: %s\n", buf);
			for(i = 0; i < sizeof(buf); i++)
				buf[i] = '\0';
			scanf("%s", buf);
			printf("sent: %s\n", buf);
			write(fd[1], buf, sizeof(buf));
		}
		close(fd[1]);
		close(pd[0]);
		exit(0);
	}
	return 0;
}
