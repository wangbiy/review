#pragma once
#include <iostream>
using namespace std;
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <stdlib.h>
#include <cstring>
//实现一个UDP网络程序
//服务端实现
class Server
{
	private:
		int sock;
		int port;
		string ip;
	public:
		Server(string _ip="127.0.0.1",int _port=8080)
			:ip(_ip)
			 ,port(_port)
			 ,sock(-1)
	{}
		void InitServer()
		{
			sock=socket(AF_INET,SOCK_DGRAM,0);//创建套接字
			if(sock<0)
			{
				cerr<<"socket error"<<endl;
				exit(2);//退出码从2开始
			}
			cout<<"init..... socket create success"<<sock<<endl;//监听套接字
			struct sockaddr_in local;
			local.sin_family=AF_INET;
			local.sin_port=htons(port);
			local.sin_addr.s_addr=inet_addr(ip.c_str());//用上地址转换函数

		   if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
		   {
			   cerr<<"bind error"<<endl;
			   exit(3);
		   }	   
		   cout<<"init..... socket bind success"<<sock<<endl;
		}

		//启动服务器,收到客户端的信息，发送响应
		void Start()
		{
			char buf[1024];
			for(;;)
			{
				struct sockaddr_in peer;//对端地址
				socklen_t len=sizeof(peer);
				ssize_t s=recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&peer,&len);
				if(s>0)//表示收到了消息
				{
					buf[s]=0;
					cout<<"client#"<<buf<<endl;
					//进行响应
					sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&peer,len);
				}

			}

		}
		~Server()
		{}
};
