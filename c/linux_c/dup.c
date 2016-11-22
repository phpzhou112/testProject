#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

//测试dup和dup2的用法
int main()
{
	int fd = open("3.txt",O_CREAT|O_APPEND|O_RDWR);
	int fds = open("2,txt",O_CREAT|O_APPEND|O_RDWR);
	char buf[] = "this is 2.txt";
	dup2(fd,fds);
	close(fd);
	if(write(fds,buf,sizeof(buf)) != sizeof(buf))
		perror("write error!");
	close(fds);
//	dup2(fd,1);
//	close(fd);
//	printf("this is test dup2 function");
	printf("%d\n",fd);
	return 0;
}
