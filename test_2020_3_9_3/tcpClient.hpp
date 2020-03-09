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
class Client
{
	private:
		int sock;
		string server_ip;
		int server_port;
	public:
		Client(string ip,int port)
			:sock(-1)
			 ,server_ip(ip)
			 ,server_port(port)
	{}
		void InitClient()
		{
			sock=socket(AF_INET,SOCK_STREAM,0);
			if(sock<0)
			{
				cerr<<"socket error"<<endl;
				exit(2);
			}
			cout<<"init socket create success"<<sock<<endl;
		}
		void Run()
		{
			struct sockaddr_in server;
			server.sin_family=AF_INET;
			server.sin_addr.s_addr=inet_addr(server_ip.c_str());
			server.sin_port=htons(server_port);
			if(connect(sock,(struct sockaddr*)&server,sizeof(server))<0)
			{
				cerr<<"connect error"<<endl;
				return;
			}
			//连接成功，进行IO操作
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
