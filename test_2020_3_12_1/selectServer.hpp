#pragma once
#include <iostream>
using namespace std;
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <stdlib.h>
#include <sys/select.h>
#define SIZE sizeof(fd_set)*8
class selectServer
{
	private:
		int port;
		int lsock;
	public:
		selectServer(int _port=8888)
			:lsock(-1)
			 ,port(_port)
	{}
		void InitServer()
		{
			lsock=socket(AF_INET,SOCK_STREAM,0);
			if(lsock<0)
			{
				cerr<<"socket error"<<endl;
				exit(2);
			}
			cout<<"init socket create success"<<lsock<<endl;
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
		}
		void Run()
		{
			int fd_array[SIZE];//保存历史上获取的文件描述符
			for(int i=0;i<SIZE;++i)
			{
				fd_array[i]=-1;
			}
			fd_set rfds;//定义读文件描述符集
			fd_array[0]=lsock;//第一个参数是套接字，其他是-1
			int max=lsock;//文件描述符最大值
			for(;;)
			{
				struct sockaddr_in peer;
				socklen_t len=sizeof(peer);
				struct timeval timeout = {0,0};//每隔0秒钟timeout
				FD_ZERO(&rfds);//将读文件描述符集初始化为0
				for(int i=0;i<SIZE;++i)
				{
					if(fd_array[i]==-1)
						continue;//不用设置
					FD_SET(fd_array[i],&rfds);//将读文件描述符集设进数组中
					if(fd_array[i]>max)
						max=fd_array[i];
				}
			switch(select(max+1,&rfds,nullptr,nullptr,nullptr))//以阻塞方式等待
			{
				case 0:
					cout<<"timeout"<<endl;
					break;
				case -1:
					cerr<<"select error"<<endl;
					break;
				default://已经就绪的文件描述符个数
					for(int i=0;i<SIZE;++i)
					{
						if(fd_array[i]==-1)
							continue;
						if(FD_ISSET(fd_array[i],&rfds))//判断该文件描述符是否在读文件描述符集中
						{
							//先判断是不是lsock
							if(fd_array[i]==lsock)//进行accept
							{
								int fd=accept(lsock,(struct sockaddr*)&peer,&len);
								if(fd<0)
								{
									cerr<<"accept error"<<endl;
									continue;
								}
								cout<<"get a new link..."<<endl;
								//将新获得的文件描述符添加进数组中
								int j=1;
								for(;j<SIZE;++j)
								{
									if(fd_array[j]==-1)
										break;
								}
								//如果这个数组的这个位置是-1，说明还没有占用
								if(j==SIZE)//数组被放满
								{
									cout<<"fd array is full"<<endl;
									close(fd);
								}
								else
								{
									fd_array[j]=fd;
								}
							}
							else//普通文件描述符
							{
								//开始读写
								char buf[1024];
								ssize_t s=recv(fd_array[i],buf,sizeof(buf)-1,0);
								if(s>0)
								{
									buf[s]=0;
									cout<<"client#"<<buf<<endl;
									send(fd_array[i],buf,strlen(buf),0);
								}
								else if(s==0)
								{
									cout<<"client quit"<<endl;
									close(fd_array[i]);
									fd_array[i]=-1;
								}
								else
								{
									cerr<<"recv error"<<endl;
									close(fd_array[i]);
									fd_array[i]=-1;
								}
							}
						}
					}
					break;
				}
			}
		}
		~selectServer()
		{
			if(lsock>0)
				close(lsock);
		}
};
