#pragma once
#include <iostream>
using namespace std;
#include <sys/socket.h>
#include <sys/types.h>
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
		string peer_ip;//服务端IP
		int peer_port;//服务端端口号
	public:
		Client(string _ip,int _port)
			:peer_ip(_ip)
			 ,peer_port(_port)
	{
		sock=-1;
	}
		void InitClient()
		{
			sock=socket(AF_INET,SOCK_DGRAM,0);
			if(sock<0)
			{
				cerr<<"socket error"<<endl;
				exit(2);
			}
			//客户端就不用绑定了
		}
		void Run()
		{
			bool quit=false;
			string message;
			char buf[1024];//用来接收服务端返回的响应
			while(!quit)
			{
				struct sockaddr_in peer;
				peer.sin_family=AF_INET;
				peer.sin_port=htons(peer_port);
				peer.sin_addr.s_addr=inet_addr(peer_ip.c_str());
				socklen_t len=sizeof(peer);
				cout<<"Please Enter#";
				cin>>message;
				sendto(sock,message.c_str(),message.size(),0,(struct sockaddr*)&peer,len);
				//接收响应
				ssize_t s=recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&peer,&len);
				if(s>0)
				{
					buf[s]=0;
					cout<<"server echo#"<<buf<<endl;
				}
			}
		}
		~Client()
		{}
};
