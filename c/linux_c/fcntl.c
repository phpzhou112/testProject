#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>

int main()
{
	char buf[1024];
	int flag;
	fcntl(STDEIN_FILENO,F_GETFL);
	flag |= O_NONBLOCK;
	if(fcntl(STDIN_FILENO,F_SETFL,flag)==-1)
	{
		perror("exit");
		exit(-1);
	}
	return 0;
}
