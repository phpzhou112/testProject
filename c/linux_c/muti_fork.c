#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>

void forkWork(int);
void sig_handler(int);

int main()
{
	forkWork(3);
//	daemon(0,0);
	return 0;
}

void sig_handler(int num)
{
	int status;
	pid_t pid;
	while((pid = waitpid(-1,&status,WNOHANG))>0)
	{
		if(WIFEXITED(status))
			printf("child process exitL[%d],exit code is:%d\n",pid,WEXITSTATUS(status));
		else
			printf("child process exit\n");
	}
}

void forkWork(int num)
{
//	signal(SIGCHLD,sig_handler);
	int i;
	pid_t pid;
	for(i=0;i<num;++i)
	{
		pid = fork();
		if(pid<0)
		{
			fprintf(stderr,"fork err");
			exit(-1);
		}
		else if(pid == 0)
		{
			//子进程
			printf("this is child%d,parent is:%d\n",getpid(),getppid());
			//子进程退出，否则会递归创建进程
			exit(-1);
		}
	}
	printf("main process is:%d\n",getpid());
//	waitpid(-1,NULL,0);
//	sleep(5);
//	sleep(5);
//	sleep(5);
	//父进程不退出，等待子进程退出，并回收子进程
	while(1)
	{
		waitpid(-1,NULL,0);
	}
}
