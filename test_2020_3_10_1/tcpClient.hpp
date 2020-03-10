#pragma once
#include <iostream>
using namespace std;
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <cstring>
#include <unistd.h>
class Client
{
	private:
		int sock;
		int server_port;
		string server_ip;
	public:
		Client(string ip="127.0.0.1",int port=8080)
			:sock(-1)
			 ,server_ip(ip)
			 ,server_port(port)
	{}
		~Client()
		{
			if(sock>0)
			{
				close(sock);
			}
		}
		void InitClient()
		{
			sock=socket(AF_INET,SOCK_STREAM,0);
			if(sock<0)
			{
				cerr<<"socket error"<<endl;
				exit(2);
			}
			cout<<"init...socket success"<<sock<<endl;
		}
		void Run()
		{
			struct sockaddr_in server;
			server.sin_family=AF_INET;
			server.sin_port=htons(server_port);
			server.sin_addr.s_addr=inet_addr(server_ip.c_str());
			if(connect(sock,(struct sockaddr*)& server,sizeof(server))<0)
			{
				cerr<<"connect error"<<endl;
				return;
			}
			cout<<"connect success"<<endl;
			//开始发送消息
			string message;
			char buf[1024];
			while(1)
			{
				cout<<"Please Enter#";
				cin>>message;
				write(sock,message.c_str(),message.size());
				ssize_t s=read(sock,buf,sizeof(buf)-1);
				if(s>0)
				{
					buf[s]=0;
					cout<<"server echo#"<<buf<<endl;
				}
			}
		}
};
