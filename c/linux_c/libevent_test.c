#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<event.h>
#include<event2/bufferevent.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

#define PORT 8000
int getSocket(const char *str,short port);
void read_cb(struct bufferevent* bev,void *arg);
void event_cb(struct bufferevent* bev,short event,void* arg);
void accept_cb(int fd,short events,void *arg);


int main(int argc, char** argv) {
	int fd = getSocket("0.0.0.0",PORT);
	struct event_base *base = event_base_new();
	struct event *listener = event_new(base,fd,EV_READ|EV_PERSIST,accept_cb,base);
	event_add(listener,NULL);
	event_base_dispatch(base);
	event_base_free(base);
	return 0;
}


int getSocket(const char *str,short port)
{
	int fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd<0)
	{
		fprintf(stderr,"socket创建失败");
		exit(-1);
	}
	evutil_make_listen_socket_reuseable(fd); //允许多次绑定同一地址
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);
	memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(str);
	if(bind(fd,(struct sockaddr*)&addr,len) < 0){
		fprintf(stderr,"bind error");
		exit(-1);
	}
	if(listen(fd,10)<0){
		fprintf(stderr,"listen error");
		exit(-1);
	}
	evutil_make_socket_nonblocking(fd);	
	return fd;
}


void read_cb(struct bufferevent* bev,void *arg){
	//读缓冲区
	 char msg[4096];
	 size_t len = bufferevent_read(bev,msg,sizeof(msg));
	 msg[len] = '\0';
	 printf("receive from client: %s\n",msg);
	 //测试回复信息
	 char replyMsg[4096] = "I receive from client is:";
	 strcat(replyMsg+strlen(replyMsg), msg);
	 //回复信息 
	 bufferevent_write(bev,replyMsg,strlen(replyMsg)); 
}


void event_cb(struct bufferevent* bev,short event,void* arg)
{
	if (event & BEV_EVENT_EOF)
        printf("connection closed\n");
    else if (event & BEV_EVENT_ERROR)
        printf("some other error\n");

    //这将自动close套接字和free读写缓冲区
    bufferevent_free(bev);
}
void accept_cb(int fd,short events,void *arg){
	struct sockaddr_in clientAddr;
	memset(&clientAddr,0,sizeof(clientAddr));
	socklen_t len = sizeof(clientAddr);
	evutil_socket_t client = accept(fd,(struct sockaddr*)&clientAddr,&len);
	if(client<0){
		fprintf(stderr,"accept error");
		return;
	}
	evutil_make_socket_nonblocking(client);//设置非阻塞 
	printf("client addr%s\n",inet_ntoa(clientAddr.sin_addr));
	//接受base 
	struct event_base *base = (event_base*)arg;
	//使用bufferevent
	bufferevent *bev = bufferevent_socket_new(base,client,BEV_OPT_CLOSE_ON_FREE);
	bufferevent_setcb(bev,read_cb,NULL,event_cb,arg);
	bufferevent_enable(bev,EV_READ|EV_PERSIST);	
}

