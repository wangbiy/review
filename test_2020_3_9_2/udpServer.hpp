#pragma once
#include <iostream>
using namespace std;
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <cstring>
map<string ,string> dict;//词典
class Server
{
	private:
		int sock;
		string ip;
		int port;
	public:
		Server(string _ip="127.0.0.1",int _port=8080)
			:sock(-1)
			 ,port(_port)
			 ,ip(_ip)
	{}
		void InitServer()
		{

			dict.insert(pair<string,string>("apple","苹果"));
			dict.insert(pair<string,string>("banana","香蕉"));
			dict.insert(pair<string,string>("orange","橘子"));
			sock=socket(AF_INET,SOCK_DGRAM,0);
			if(sock<0)
			{
				cerr<<"socker error"<<endl;
				exit(2);
			}
			cout<<"int....socket create success"<<sock<<endl;
			struct sockaddr_in local;
			local.sin_family=AF_INET;
			local.sin_port=htons(port);
			local.sin_addr.s_addr=inet_addr(ip.c_str());
			if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
			{
				cerr<<"bind error"<<endl;
				exit(3);
			}
			cout<<"init.....bind success"<<sock<<endl;
		}
		void Start()
		{
			char buf[1024];
			for(;;)
			{
				struct sockaddr_in peer;
				socklen_t len=sizeof(peer);
				ssize_t s= recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&peer,&len);
				if(s>0)
				{
					buf[s]=0;
					string key=buf;
					string value;//服务端接收到客户端发来的key,翻译出value
					auto it=dict.find(key);
					if(it!=dict.end())
					{
						value=dict[key];
					}
					else
						value="unknow";
					cout<<"client#"<<buf<<endl;
					//将value响应给客户端
					sendto(sock,value.c_str(),value.size(),0,(struct sockaddr*)&peer,len);
				}
			}
		}
		~Server()
		{}
};
