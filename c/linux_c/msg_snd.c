#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<errno.h>
#include<string.h>

typedef struct Msg
{
	long type;
	char szBuf[1024];
}MSG_S;

void testSnd()
{
	MSG_S msg = {0};
	key_t key = ftok("a.txt",1);
	if(key == -1)
	{
		perror("ftok error");
		return;
	}
	int msgid = msgget(key,IPC_CREAT);
	if(msgid == -1)
	{
		perror("msgget error");
		return;
	}
	char mode;
	fprintf(stderr,"input your mode [r/w]:");
	mode = getchar();
	if('w' == mode)
	{
		while(1)
		{
			
			fprintf(stderr,"send:");
			scanf("%ld%s",&(msg.type),msg.szBuf);
			int iRet = msgsnd(msgid,&msg,strlen(msg.szBuf),0);
			if(iRet == -1)
			{
				perror("msgsnd error");
				break;
			}
		}
	}else if('r' == mode)
	{
		while(1)
		{
			//input type
			printf("want to recv msg type: ");
			scanf("%ld",&(msg.type));
			if(msgrcv(msgid,&msg,1024,msg.type,0) != -1)
			{
				printf("%s\n",msg.szBuf);
			}
			
		}
	}
}


int main(int argc,char** argv)
{
	testSnd();
	return 0;
}
