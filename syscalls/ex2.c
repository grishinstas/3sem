#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
int main()
{
	int i;
	key_t key = ftok("file.c", 100);
	int m = msgget(key, 0666|IPC_CREAT);
	struct msgbuf {
		long type;
		int length;
		char buf[4096];
	} mb;
	mb.type = 1;
	for(i = 0; i < 4096; i++)
		mb.buf[i] = 0;
	int fd = open("a.txt", O_RDONLY);
	while((mb.length = read(fd, mb.buf, 4096)) > 0)
		msgsnd(m, *mb, 4096, 0);
	close(fd);
	msgsnd(m, *mb, 4096, 0);
	return 0;
}
// sender



#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
int main()
{
	key_t key = ftok("file.c", 100);
	int m = msgget(key, 0666|IPC_CREAT);
	struct msgbuf {
		long type;
		int length;
		char buf[4096];
	} mb;
	int fd = open("b.txt", O_WRONLY|O_CREAT|O_TRUNC);
	msgrcv(m, *mb, 4096, 1, 0);
	while(mb.length > 0) {
		write(fd, mb.buf, mb.length);
		msgrcv(m, *mb, 4096, 1, 0);
	}
	close(fd);
	msgctl(m, IPC_RMID, NULL);
	return 0;
}
// receiver
