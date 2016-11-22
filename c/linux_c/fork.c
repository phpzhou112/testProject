#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/types.h>
int main()
{
	char *message;
	pid_t pid;
	int i;
	pid = fork();
	if(pid<0)
	{
		perror("创建进程失败\n");
		exit(-1);
	}
	if(pid == 0)
	{
	//	printf("子进程\n");
		message = "这个是子进程\n";
		execl("/bin/curl","curl","pid,ppid,pgrp,session,tpgid,comm",NULL);
//		i = 6;
	}
	else
	{
	//	waitpid();
	//	printf("父进程\n");
		message = "这个是父进程\n";
		i=3;
	}

	for(;i>0;i--)
	{
		printf(message);
		sleep(1);
	}
	printf("main程序\n");
	return 0;
}
