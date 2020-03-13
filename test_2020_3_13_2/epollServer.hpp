#include <iostream>
using namespace std;
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <stdlib.h>
class Server
{
	private:
		int lsock;
		int port;
		int epfd;
	public:
		Server(int _port=8888)
			:lsock(-1)
			 ,port(_port)
			 ,epfd(-1)
	{}
		void InitServer()
		{
			lsock=socket(AF_INET,SOCK_STREAM,0);
			if(lsock<0)
			{
				cerr<<"socket error"<<endl;
				exit(2);
			}
			cout<<"socket create success"<<lsock<<endl;
			struct sockaddr_in local;
			local.sin_family=AF_INET;
			local.sin_port=htons(port);
			local.sin_addr.s_addr=htonl(INADDR_ANY);
			if(bind(lsock,(struct sockaddr*)& local,sizeof(local))<0)
			{
				cerr<<"bind error"<<endl;
				exit(3);
			}
			cout<<"bind success"<<endl;
			if(listen(lsock,5)<0)
			{
				cerr<<"listen error"<<endl;
				exit(4);
			}
			cout<<"listen success"<<endl;
			int opt=1;
			setsockopt(lsock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
			if((epfd=epoll_create(256))<0)
			{
				cerr<<"epoll_create error"<<endl;
				exit(5);
			}
		}
		void HanderEvents(int epfd,struct epoll_event* revs,int num)
		{
			struct epoll_event ev;
			for(int i=0;i<num;++i)
			{
				int sock=revs[i].data.fd;
				if(revs[i].events & EPOLLIN)//检测是否有读事件就绪
				{
					if(sock==lsock)
					{
						//获取新连接
						struct sockaddr_in peer;
						socklen_t len=sizeof(peer);
						int new_sock=accept(lsock,(struct sockaddr*)&peer,&len);
						if(new_sock<0)
						{
							cerr<<"accept error"<<endl;
							continue;
						}
						cout<<"get a new link"<<new_sock<<endl;
						//将其加入epoll模型中
						ev.events=EPOLLIN;
						ev.data.fd=new_sock;
						epoll_ctl(epfd,EPOLL_CTL_ADD,new_sock,&ev);
					}
					else//普通文件描述符
					{
						char buf[1024];
						ssize_t s=recv(sock,buf,sizeof(buf)-1,0);
						if(s>0)
						{
							buf[s]=0;
							cout<<"client#"<< buf<<endl;
							//改为写
							ev.events=EPOLLOUT;
							ev.data.fd=sock;
							epoll_ctl(epfd,EPOLL_CTL_MOD,sock,&ev);
						}
						else if(s==0)
						{
							cout<<"link close"<<endl;
							close(sock);
							epoll_ctl(epfd,EPOLL_CTL_DEL,sock,nullptr);
						}
						else
						{
							cout<<"recv error"<<endl;
							close(sock);
							epoll_ctl(epfd,EPOLL_CTL_DEL,sock,nullptr);
						}
					}
				}
				else if(revs[i].events & EPOLLOUT)//检查写事件是否就绪
				{
					string http_echo="HTTP/1.1 200 OK\r\n\r\n<html><body><h1>hello EPOLL Server</h1></body></html>";
					send(sock,http_echo.c_str(),http_echo.size(),0);
					close(sock);//发完就关掉，短连接
					epoll_ctl(epfd,EPOLL_CTL_DEL,sock,nullptr);
				}
				else
				{
					cout<<"bug?"<<endl;
				}
			}
		}
		void Run()
		{
			//先将lsock注册进epoll模型
			struct epoll_event ev;
			ev.events=EPOLLIN;
			ev.data.fd=lsock;
			epoll_ctl(epfd,EPOLL_CTL_ADD,lsock,&ev);
			struct epoll_event revs[128];
			for(;;)
			{
				int timeout=-1;
				int num=0;
				switch((num=epoll_wait(epfd,revs,128,timeout)))
				{
					case 0:
						cout<<"time out"<<endl;
						break;
					case -1:
						cout<<"epoll wait error"<<endl;
						break;
					default:
						HanderEvents(epfd,revs,num);//处理事件
						break;
				}
			}
		}
		~Server()
		{
			if(lsock>=0)
			{
				close(lsock);
			}
			if(epfd>=0)
			{
				close(epfd);
			}
		}
};
