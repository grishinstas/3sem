#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv, char *envp)
{
                        char path[255], pathargs[4096];
                        int i;
                        if(argc > 1) {
                                pid_t pid = fork();
                                if (pid) {
                                        int status;
                                        waitpid(pid, &status, 0);
                                        printf("ret code=%d\n", WEXITSTATUS(status));
                                }
                                else {
                                execvp(argv[1], argv + 1);
                                printf("exec error");
                                return -1;
                                }
                        }
                                while(1) {
                                char pathargs[256];
                                char vector[256][256];
                                char *pointer[256];
                                printf("Enter the command or press Ctrl-C for exit>");
                                gets(pathargs);
                                int i, j, k;
                                i = j = 0;
                                while(pathargs[i] != '\0') {
                                        k = 0;
                                        while (pathargs[i] != ' ' && pathargs[i] != '\0') {
                                                vector[j][k] = pathargs[i];
                                                i++;
                                                k++;
                                        }
                                        vector[j][k] = '\0';
                                        pointer[j] = vector[j];
                                        j++;
                                        if(pathargs[i] != '\0')
                                                i++;
                                        }
                                pointer[j] = (char *) NULL;
                                pid_t pid = fork();
                                if (pid) {
                                        int status;
                                        waitpid(pid, &status, 0);
                                        printf("ret code=%d\n", WEXITSTATUS(status));
                                }
                                else {
                                execvp(*pointer, pointer);
                                printf("exec error\n");
                                return -1;
                                } 
        }
        return 0;
}
