#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
  int fd = open("a.txt", O_RDONLY);
  if(fd < 0) {
    printf("open error");
    exit(-1);
  }
  int length = lseek(fd, 0, SEEK_END);
  if (length < 0) {
    printf("lseek error");
    exit(-1);
  }
  int dst = open("b.txt", O_WRONLY|O_CREAT|O_TRUNC);
  if (dst < 0) {
    printf("open error");
    exit(-1);
  }
  void * m = mmap(NULL, length, PROT_WRITE, MAP_SHARED, dst, 0);
  if (m == MAP_FAILED) {
    printf("mmap error");
    exit(-1);
  }
  close(dst);
  void * n = mmap(m, length, PROT_READ, MAP_SHARED, fd, 0);
  if(n != m) {
    printf("mmap error");
    exit(-1);
  }
  close(fd);
  return 0;
}
