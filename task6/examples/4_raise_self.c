#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
char a = 0;
int n = 1;
char *aa = &a;
int *nn = &n;
void handler1(int sig) {
        *nn *= 2;
}
void handler2(int sig) {
   *aa += *nn;
    *nn *= 2;
}
int main() {
        int fd2 = open("b.txt", O_WRONLY | O_CREAT | O_TRUNC);
         pid_t pid = fork();
        if(pid < 0) {
                printf("fork error");
                exit(-1);
        }
        if (pid == 0) {
        int fd1 = open("a.txt", O_RDONLY);
        while(read(fd1, &a, sizeof(char)) > 0) {
            n = 1;
            while(n != 256) {
                if(a & n)
                    kill(getppid(), SIGUSR2);
                else
                    kill(getppid(), SIGUSR1);
                n *= 2;
        raise(SIGSTOP);
           }
        }
        close(fd1);
        close(fd2);
        kill(getppid(), SIGKILL);
        return 0;
    }
    else {
        signal(SIGUSR1, handler1);
        signal(SIGUSR2, handler2);
        while(1) {
            if (*nn == 256) {
                 write(fd2, aa, sizeof(char));
               *aa = 0;
                *nn = 1;
            }
            kill(pid, SIGCONT);
        }
        return 0;
    }
}
