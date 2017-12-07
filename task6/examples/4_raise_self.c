#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
void handler1(int sig, char *a, char *n) {
    *n *= 2;
}
void handler2(int sig, char *a, char *n) {
    *a += *n;
    *n *= 2;
}
 
int main() {
    pid_t pid = fork();
    if (pid) {
        pid = getpid() + 1;
        int fd = open("a.txt", O_RDONLY);
        while(read(fd, *a, 1) > 0)
            for(n = 1; n; n *= 2)
                if(a & n)
                    kill(pid, SIGUSR2);
                else
                    kill(pid, SIGUSR1);
        close(fd);
        kill(pid, SIGKILL);
        return 0;
    }
    else {
        signal(SIGUSR1, handler1);
        signal(SIGUSR2, handler2);
        char *a, *n;
        *a = 0;
        *n = 1;
        open("b.txt", O_WRONLY | O_CREAT | O_TRUNC);
        while(1)
            if (*n == 0) {
                write(fd, a, 1);
                *a = 0;
                *n = 1;
            }
        return 0;
    }
