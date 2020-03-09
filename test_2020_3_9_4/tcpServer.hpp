#pragma once
#include <iostream>
using namespace std;
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string>
#include <cstring>
#include <stdlib.h>
//多线程的tcp通信程序
class Server
{
	private:
		int listen_sock;
		//string ip;//可以不需要ip地址了
		int port;
	public:
		Server(int _port=8080)
			:listen_sock(-1)
			 ,port(_port)
	{}
		void InitServer()
		{
			listen_sock=socket(AF_INET,SOCK_STREAM,0);
			if(listen_sock<0)
			{
				cerr<<"socket error"<<endl;
				exit(2);
			}
			cout<<"init...socket create success"<<listen_sock<<endl;
			struct sockaddr_in local;
			local.sin_family=AF_INET;
			local.sin_port=htons(port);
			local.sin_addr.s_addr=htonl(INADDR_ANY);//后面的IO接口使用的是recv和send，可以不需要Ip地址来运行服务端，这里将IP地址设为INADDR_ANY，其实为0,也不用原来的地址转换函数，使用htonl转为主机号
			if(bind(listen_sock,(struct sockaddr*)& local,sizeof(local))<0)
			{
				cerr<<"listen error"<<endl;
				exit(3);
			}
			cout<<"init bind success"<<listen_sock<<endl;
			if(listen(listen_sock,5)<0)
			{
				cerr<<"listen error"<<endl;
				exit(4);
			}
			cout<<"listen success"<<listen_sock<<endl;
		}
		static void ServiceIO(int sock)
		{
			//先接收消息
			char buf[1024];
			while(1)
			{
				//ssize_t s=read(sock,buf,sizeof(buf)-1);
				ssize_t s=recv(sock,buf,sizeof(buf)-1,0);//使用这种IO接口可以在进行测试时不需要输入IP地址，直接使用端口号运行服务端
				if(s>0)
				{
					buf[s]=0;
					cout<<"client#"<<buf<<endl;
					//write(sock,buf,strlen(buf));
					send(sock,buf,strlen(buf),0);
				}
				else if(s==0)
				{
					cout<<"client quit"<<endl;
					break;
				}
				else
					cout<<"read error"<<endl;
			}
		}
		static void* ThreadRun(void* arg)
		{
			pthread_detach(pthread_self());//将新线程分离，因为如果新线程退出，主线程不采用pthread_join的方式进行等待，就会产生类似于僵尸进程的问题，因此要将线程分离
			int sock =*(int*) arg;//涉及C++11中的四种类型转换
			ServiceIO(sock);
			delete (int*)arg;
			//所有的线程是共享文件描述符的，因此不能关闭文件描述符，这也是与多进程之间的不同，但是多线程可以在服务完成+之后关闭文件描述符
			 close(sock);
		}
		void Start()
		{
			struct sockaddr_in peer;
			while(true)
			{
				socklen_t len=sizeof(peer);
				int sock=accept(listen_sock,(struct sockaddr*)& peer,&len);
				if(sock<0)
				{
					cerr<<"accept error"<<endl;
					continue;
				}
				cout<<"get a new link[IP:PORT]"<<inet_ntoa(peer.sin_addr)<<":"<<ntohs(peer.sin_port)<<endl;
				//开始创建线程
				 pthread_t tid;
				 int* p=new int(sock);//由于sock是int类型的，我们在实现ThreadRun函数时无法直接将void*转换为int，因此用p指向sock，然后将p作为ThreadRun的参数传进去即可
				  pthread_create(&tid,NULL,ThreadRun,(void*)p);//创建新线程
			}
		}
		~Server()
		{}
};
