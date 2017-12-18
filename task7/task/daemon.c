#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdlib.h>
#define primary_dir "/home/stas/labs"
#define temporary_dir "/home/stas/dir"
int main()
{
  pid_t pid = fork();
   if (pid) {
      umask(0);
      char buf[5];
      sprintf(buf, "%hu", pid);
      int i;
      for(i = 0; i < 5; i++)
          if(buf[i] < '0' || buf[i] > '9')
                buf[i] = ' ';
      int fd = open("pid.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
      write(fd, buf, 5);
      close(fd);
      return 0;
   }
   else {
      umask(0);
      setsid();
      chdir("/");
      close(0);
      close(1);
      close(2);
         while (1) {
            pid_t p = fork();
        if(p)
                wait(NULL);
        else {
                execlp("rm", "rm", "-r", "-f", temporary_dir , 0); //Remove previous state
        }
        int fd2 = open("/dev/null", O_WRONLY | O_CREAT | O_TRUNC);
        pid_t p1 = fork();
        if (p1) {
            wait(NULL);
            close(fd2);
        }
        else {
            dup2(fd2,2); //redirect STDERR to /dev/null
            dup2(fd2,1); //redirect STDOUT to /dev/null
            execlp("cp", "cp", "-r", primary_dir, temporary_dir, 0);
        }
         sleep(60);
         int fd3 = open("/home/stas/Documents/log.diff", O_WRONLY | O_CREAT | O_TRUNC , 0666);
         pid_t p2 = fork();
         if (p2) {
            wait(NULL);
            close(fd3);
         }
         else {
            dup2(fd3,1);
            dup2(fd3,2);
            execlp("diff", "diff", "-r", temporary_dir, primary_dir, 0);
         }
      }
      }
      return 0;
   }

