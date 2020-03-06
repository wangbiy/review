#include <iostream>
using namespace std;
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main()
{
	int fd=open("fifo",O_WRONLY);
	if(fd<0)
	{
		cout<<"open error"<<endl;
		return 1;
	}
	char buf[1024];
	while(1)//先从标准输入读到要写入管道文件的内容，放到缓冲数组buf中
	{
		cout<<"Please Enter your message:";
		fflush(stdout);//必须刷新，因为标准输入具有缓冲区，不刷新内容还在缓冲区中
		ssize_t s=read(0,buf,sizeof(buf)-1);
		if(s>0)
		{
			buf[s-1]=0;//敲了回车之后会空出来一行，接收到了这个空的行，因此将buf[s-1]=0
			write(fd,buf,strlen(buf));//将buf中的内容写入到管道文件中
		}
		else if(s==0)
		{
			cout<<"client error"<<endl;
			break;
		}
		else
		{
			cout<<"read error"<<endl;
			break;
		}
	}
	close(fd);
	return 0;
}
