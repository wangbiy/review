#include <iostream>
using namespace std;
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
int main()
{
	mkfifo("fifo",0644);
	int fd=open("fifo",O_RDONLY);
	if(fd<0)
	{
		cout<<"open error"<<endl;
		return 1;
	}
	char buf[1024];
	while(1)
	{
		ssize_t s=read(fd,buf,sizeof(buf)-1);
		if(s>0)
		{
			buf[s]=0;
			cout<<"client--->service#"<<buf<<endl;
		}
		else if(s==0)
		{
			cout<<"client exit"<<endl;
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
