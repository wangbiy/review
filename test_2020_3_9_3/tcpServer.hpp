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
#include <signal.h>
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
#if 0
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
#endif
		//上述是使用单进程实现的服务器，如果是多连接的，就不能和服务器进行正确的通信，是因为我们accept之后，就一直循环尝试read，没有继续调用accept，导致不能接受新的请求，因此，我们要实现一个多进程的基于TCP的网络程序，只需要将accept这里改一下
		void Start()
		{
			//使用fork创建子进程，在接受连接的过程中，创建子进程，子进程可以看到父进程的文件描述符，也继承了父进程的接受连接的操作，子进程进行IO操作，父进程不能以阻塞方式等待，不然就还是单进程的操作，可以通过SIGCHLD信号来通知父进程忽略方式等待，父子进程各自有一个文件描述符表，子进程最好关掉文件描述符，以防内存泄漏，最后父进程关掉文件描述符
			struct sockaddr_in peer;//对端
			signal(SIGCHLD,SIG_IGN);//将父进程设置为忽略
			while(true)
			{
				socklen_t len=sizeof(peer);
				int sock=accept(listen_sock,(struct sockaddr*)&peer,&len);
				if(sock<0)
				{
					cerr<<"accept error"<<endl;
					continue;
				}
				cout<<"get a new link[IP:PORT]"<<inet_ntoa(peer.sin_addr)<<":"<<ntohs(peer.sin_port)<<endl;//拿到客户端的ip地址，以点分二进制的方式打印，用地址转换函数将4字节的字符串转换为点分二进制的ip地址，使用inet_ntoa接口，而打印port要将网络号转换为主机号
				pid_t id=fork();
				if(id==0)//child
				{
					close(listen_sock);//不需要这个监听套接字
					ServiceIO(sock);
					close(sock);//使用完关闭
					exit(0);//子进程退出
				}
				//father
				close(sock);//父进程接收子进程SIGCHLD信号，关闭即可
			}
		}
};
