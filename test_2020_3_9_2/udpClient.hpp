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
class Client
{
	private:
		int sock;
		int peer_port;
		string peer_ip;
	public:
		Client(string ip,int port)
			:sock(-1)
			 ,peer_ip(ip)
			 ,peer_port(port)
	{}
		void InitClient()
		{
			sock=socket(AF_INET,SOCK_DGRAM,0);
			if(sock<0)
			{
				cerr<<"socket error"<<endl;
				exit(2);
			}
			cout<<"init... socket create success"<<sock<<endl;
			//不需要绑定
		}
		void Run()
		{
			bool quit=false;
			string message;
			char buf[1024];
			while(!quit)
			{
				struct sockaddr_in peer;
				socklen_t len=sizeof(peer);
				peer.sin_family=AF_INET;
				peer.sin_port=htons(peer_port);
				peer.sin_addr.s_addr=inet_addr(peer_ip.c_str());
				cout<<"Please Enter#";
				cin>>message;
				sendto(sock,message.c_str(),message.size(),0,(struct sockaddr*)&peer,len);
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
