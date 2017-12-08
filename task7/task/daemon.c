#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdlib.h>
int main()
{
 ` pid_t pid = fork();
   if (pid) {
      int fd = open("pid.txt", O_WRONLY | O_CREAT);
      pid = getpid() + 1;
      write(fd, &pid, sizeof(pid_t));
      close(fd);
      return 0;
   }
   else {
      setsid();
      chdir("\");
      close(stdin);
      close(stdout);
      close(stderr);
      DIR *d = opendir("dir");
      while (1) {
         pid_t p1 = fork();
         if (p1)
            wait();
         else
            execlp("cp", "-r", "home", "dir", 0);
         closedir(d);
         sleep(60);
         d = opendir("dir");
         int fd = open("log.diff", O_WRONLY | O_CREAT);
         pid_t p2 = fork();
         if (p2)
            wait();
         else
            execlp("diff", "-r", "dir", "home", ">", "log.diff", 0);
         close(fd);
      }
      return 0;
   }
