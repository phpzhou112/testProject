#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>

int main()
{
	time_t t;
	//结构体tm存储了时间的格式化
	struct tm *p;
	t = time(&t);
	p = localtime(&t);
	//输出格式:Y-m-d H:i:s
//	printf("%d-%d-%d %d:%d:%d\n",p->tm_year+1900,(p->tm_mon+1),p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);
//	printf("time is %s\n",ctime(&t));
	//使用strftime格式化时间
	char buf[40];
	strftime(buf,sizeof(buf),"%Y-%m-%d %I:%M:%S\n",p);
	printf("%s\n",buf);
	printf("second=%d\n",t);
	//测试gettimeofday
	struct timeval tv;
//	struct timezone tz;
	gettimeofday(&tv,NULL);
	printf("seconds = %d\n",tv.tv_sec);
	printf("useconds = %d\n",tv.tv_usec);
	return 0;
}
