#include <iostream>
using namespace std;
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
void* Routine(void* arg)
{
	int* p=(int*)arg;
	int sock=*p;
	delete p;
	char request[10240];//服务器接收到请求，存到request中
	ssize_t s=recv(sock,request,sizeof(request)-1,0);
	if(s>0)
	{
		request[s]=0;
		cout<<"---------------------"<<endl;//证明是一个请求
		cout<<request<<endl;
		cout<<"---------------------"<<endl;
		//开始响应
		string response="HTTP/1.0 302 Found\r\nLocation:https://www.baidu.com\r\n\r\n";//302是临时重定向
		send(sock,response.c_str(),response.size(),0);
	}
	else if(s==0)
	{
		cout<<"client quit"<<endl;
	}
	else
	{
		cout<<"recv error"<<endl;
	}
	close(sock);
}
int main(int argc,char* argv[])
{
	if(argc!=2)
	{
		cout<<"Usage:"<<argv[0]<<endl;
		return 1;
	}
	int port=atoi(argv[1]);
	int listen_sock=socket(AF_INET,SOCK_STREAM,0);
	if(listen_sock<0)
	{
		cerr<<"socket error"<<endl;
		return 2;
	}
	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_port=htons(port);
	local.sin_addr.s_addr=htonl(INADDR_ANY);
	if(bind(listen_sock,(struct sockaddr*)& local,sizeof(local))<0)
	{
		cerr<<"bind error"<<endl;
		return 3;
	}
	if(listen(listen_sock,5)<0)
	{
		cerr<<"listen error"<<endl;
		return 4;
	}
	for(;;)
	{
		struct sockaddr_in peer;
		socklen_t len=sizeof(peer);
		//接收请求
		int sock=accept(listen_sock,(struct sockaddr*)& peer,&len);
		if(sock<0)
		{
			cerr<<"accept error"<<endl;
			continue;
		}
		cout<<"get a new link"<<sock<<endl;
		pthread_t tid;
		int* fd=new int(sock);
		pthread_create(&tid,nullptr,Routine,(void*)fd);
	}
	return 0;
}
