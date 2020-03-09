#pragma once
#include <iostream>
using namespace std;
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
class Server
{
	private:
		int listen_sock;
		string ip;
		int port;
	public:
		Server(string _ip="127.0.0.1",int _port=8080)
			:listen_sock(-1)
			 ,port(_port)
			 ,ip(_ip)
	{}
		void InitServer()
		{
			listen_sock=socket(AF_INET,SOCK_STREAM,0);//TCP
			if(listen_sock<0)
			{
				cerr<<"socket error"<<endl;
				exit(2);
			}
			cout<<"init....socket create success"<<listen_sock<<endl;
			struct sockaddr_in local;
			local.sin_family=AF_INET;
			local.sin_port=htons(port);
			local.sin_addr.s_addr=inet_addr(ip.c_str());
			if(bind(listen_sock,(struct sockaddr*)&local,sizeof(local))<0)
			{
				cerr<<"bing error"<<endl;
				exit(3);
			}
			cout<<"init...bind success"<<listen_sock<<endl;
			if(listen(listen_sock,5)<0)
			{
				cerr<<"listen error"<<endl;
				exit(4);
			}
		}
		void ServiceIO(int sock)
		{
			char buf[1024];
			for(;;)
			{
				ssize_t s=read(sock,buf,sizeof(buf)-1);
				if(s>0)
				{
					buf[s]=0;
					cout<<"client#"<<buf<<endl;
					write(sock,buf,strlen(buf));
				}
				else if(s==0)
				{
					cout<<"client quit"<<endl;
					break;
				}
				else
					cerr<<"read error"<<endl;
			}
		}
		//开始接受连接，进行收发数据
		void Start()
		{
			struct sockaddr_in peer;//对端地址
			while(true)
			{
				socklen_t len=sizeof(peer);
				int sock=accept(listen_sock,(struct sockaddr*)&peer,&len);//sock是新的文件描述符,即接收了新连接，有了新的文件描述符
				if(sock<0)
				{
					cerr<<"accept error"<<endl;
					continue;//不是结束，没有接受连接，没有影响
				}
				cout<<"get a new link"<<sock<<endl;
				//进行读写数据
				ServiceIO(sock);//对新连接进行IO操作
				close(sock);//关掉新连接，以防内存泄漏
			}
		}
};
