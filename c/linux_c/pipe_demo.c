#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<sys/fcntl.h>
#include<wait.h>

#define MAXSIZE 1024

void TestPipe()
{
	int fds[2];

	printf("My pid %d\n", getpid());

	if (pipe(fds) != 0)
	{
		perror("Fail to pipe");
		return;	
	}

	printf("fds = {%d, %d}\n", fds[0], fds[1]);

	char szBuf[100];

	pid_t pid = fork();
	
	if (pid == 0)
	{
		//child - process
		printf("Child pid %d\n", getpid());

		close(fds[1]);  //close fd for write

		while(1)
		{
			memset(szBuf, 0, 100);
			read(fds[0], szBuf, 100);
			printf("Child receive: %s\n", szBuf);			
		}
		close(fds[0]);

		return;
	}
	else
	{
		close(fds[0]);
		while(1)
		{
			usleep(10000);
			fprintf(stderr, "Send:");
			scanf("%s", szBuf);
			memset(szBuf, 0, 100);
			read(0, szBuf, 100);
			write(fds[1], szBuf, strlen(szBuf));
		}
		close(fds[1]);

		return;
	}

}

void TestDblPipe()
{
	int fdsa[2]; //parent --> child
	int fdsb[2]; //child  --> parent

	printf("My pid %d\n", getpid());

	if (pipe(fdsa) || pipe(fdsb))
	{
		perror("Fail to pipe");
		return;
	}

	char szBuf[100];
	pid_t pid = fork();

	if (pid == 0)
	{
		printf("Child pid %d\n", getpid());

		close(fdsa[1]);
		close(fdsb[0]);
		
		while(1)
		{
			memset(szBuf, 0, 100);
			read(fdsa[0], szBuf, 100);

			int i;
			for (i=0; i<strlen(szBuf); i++)
			{
				szBuf[i] = toupper(szBuf[i]);
			}

			write(fdsb[1], szBuf, strlen(szBuf));
		}
		close(fdsa[1]);
		close(fdsb[0]);
	}
	else
	{
		close(fdsa[0]);
		close(fdsb[1]);
		usleep(10000);
		while(1)
		{
			fprintf(stderr, "Send:");
			memset(szBuf, 0, 100);
			read(0, szBuf, 100); //read stdin

			write(fdsa[1], szBuf, strlen(szBuf)); //send szBuf to child-process

			read(fdsb[0], szBuf, 100);

			printf("Upper:%s", szBuf);
		}
		close(fdsa[1]);
		close(fdsb[0]);
		return;
	}

	return;
}

void TestDupForPipe()
{
	int fds[2];

	if (pipe(fds))
	{
		perror("Fail to pipe");
		return;
	}

	pid_t pid = fork();

	if (pid == 0)
	{
		//child process
		close(fds[1]);
		dup2(fds[0], 0);//redirect stdin to fds[0]
		execlp("grep", "grep", "pts", NULL);		
	}
	else
	{
		close(fds[0]);

		int fd = open("a.txt", O_RDONLY);
		if (fd < 0)
		{
			printf("error: File %s, Line %d\n ", __FILE__, __LINE__);
			perror("Fail to open");
			return;
		}
//		wait(NULL);
		char szLine[100];
		
		while(1)
		{
			int iRet = read(fd, szLine, 100);
			if (iRet < 0)
			{
				perror("Fail to read");
			}
			else if (iRet == 0)
			{
				break;
			}
			else
			{
				write(fds[1], szLine, strlen(szLine));
			}
		}
		close(fds[1]);
		return;
	}	

}

void TestPopen()
{
	int arr[] = {1,4,7,2,5,8,9,6,3,};

	FILE *pFile = popen("sort -n", "w");
	if (!pFile)
	{
		perror("popen failed");
		return;
	}
	
	int i;
	for (i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
	{
		fprintf(pFile, "%d\n", arr[i]);		
	}
	
	pclose(pFile);
	
	return;
}

//使用popen实现ps -ef|grep pts
void TestPopen2()
{
	FILE *pread;
	FILE *pwrite;
	if(NULL == (pread= popen("ps -ef","r")))
	{
		perror("pread popen error");
		return;
	}
	if(NULL == (pwrite=popen("grep pts","w")))
	{
		perror("pwrite popen error");
		pclose(pread);
		return;
	}
	char buf[MAXSIZE];
	while(fread(buf,MAXSIZE,1,pread))
	{
		fwrite(buf,MAXSIZE,1,pwrite);
	}
}

int main()
{
//	TestPipe();
//	TestDblPipe();

//	TestDupForPipe();

	//TestPopen();
	TestPopen2();
	return 0;	
}

