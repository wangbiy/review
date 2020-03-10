#pragma once
#include "ThreadPool.hpp"
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
class Server
{
	private:
		int listen_sock;
		int port;
		ThreadPool* tp;//线程池
	public:
		Server(int _port=8080)
			:listen_sock(-1)
			 ,port(_port)
			 ,tp(nullptr)
	{}
		~Server()
		{
			if(listen_sock>0)
			{
				close(listen_sock);
			}
			delete tp;//销毁线程池
		}
		void InitServer()
		{
			listen_sock=socket(AF_INET,SOCK_STREAM,0);
			if(listen_sock<0)
			{
				cerr<<"socket error"<<endl;
				exit(2);
			}
			cout<<"init....socket create success"<<listen_sock<<endl;
			struct sockaddr_in local;
			local.sin_family=AF_INET;
			local.sin_port=htons(port);
			local.sin_addr.s_addr=htonl(INADDR_ANY);
			if(bind(listen_sock,(struct sockaddr*)& local,sizeof(local))<0)
			{
				cerr<<"bind error"<<endl;
				exit(3);
			}
			cout<<"bind success"<<listen_sock<<endl;
			if(listen(listen_sock,5)<0)
			{
				cerr<<"listen error"<<endl;
				exit(4);
			}
			cout<<"listen success"<<endl;
			//创建线程池
			tp=new ThreadPool();
			tp->InitPthreadPool();
		}
		void Start()
		{
			struct sockaddr_in peer;
			while(1)
			{
				socklen_t len=sizeof(peer);
				int sock=accept(listen_sock,(struct sockaddr*)& peer,&len);
				if(sock<0)
				{
					cerr<<"accept error"<<endl;
					continue;
				}
				cout<<"get a new link[IP:PORT]"<<inet_ntoa(peer.sin_addr)<<":"<<ntohs(peer.sin_port)<<endl;
				Task t(sock);//将套接字交给线程池
				tp->PushTask(t);//线程池将任务放进去
			}
		}
};
