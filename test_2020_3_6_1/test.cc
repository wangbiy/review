#include <iostream>
using namespace std;
#include <unistd.h>
#include <string.h>
//进程间通信
//匿名管道，使用
//只能用于具有亲缘关系的进程之间通信
#if 0
int main()
{
	int fd[2]={0};
	pipe(fd);
	pid_t id=fork();
	if(id==0)//child
	{
		close(fd[0]);//关闭读
		char message[]="I am a chile,i am alive!\n";
		while(1)
		{
			write(fd[1],message,strlen(message));
			sleep(1);
		}
	}
	else//father
	{
		close(fd[1]);//关闭写
		char buf[1024];
		while(1)
		{
			size_t s=read(fd[0],buf,sizeof(buf)-1);
			if(s>0)
			{
				buf[s]=0;
				cout<<"I am father,got child message:"<<buf<<endl;
			}
		}
	}
	return 0;
}
#endif
//管道读写规则
#if 0
//1.写端一只写，读端不读，管道满了，write调用阻塞，直到有进程来读走数据
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
	int fd[2]={0};
	pipe(fd);//创建管道
	pid_t id=fork();
	if(id==0)//child
	{
		close(fd[0]);//关闭读端
		const char* str="I am child";
		int count=0;
		while(1)
		{
			write(fd[1],str,strlen(str));//写端一只写
			count+=strlen(str);
			cout<<count<<endl;
		}
	}
	else//father
	{
		close(fd[1]);//关闭写端，不读
		//直接阻塞等待
		char buf[1024];
		waitpid(id,nullptr,0);
	}
	//子进程写端一只写，父进程读端不读，子进程写满就阻塞了
	return 0;
}
#endif
#if 0
//2.读端一直读，写端不写，管道没有数据可读了，read调用阻塞，一直等到有数据来到为止
#include <unistd.h>
int main()
{
	int fd[2]={0};
	pipe(fd);
	pid_t id=fork();
	if(id==0)//child
	{
		close(fd[0]);
		const char* str="I am child";
		int count=0;
		while(1)
		{
			write(fd[1],str,strlen(str));
			count+=strlen(str);
			cout<<count<<endl;
		}
		exit(0);
		//子进程写端一瞬间写完，直接退出
	}
	else//father
	{
		close(fd[1]);
		char buf[1024];
		while(1)
		{
			sleep(5);
			size_t s=read(fd[0],buf,sizeof(buf)-1);
			if(s>0)
			{
				buf[s]=0;
				cout<<buf<<endl;
			}
			else if(s==0)//说明读的文件已经到达了末尾
			{
				cout<<"read file end"<<endl;
				break;	
			}
			else
			{
				cout<<"read file error"<<endl;
				break;
			}
		}
	}
	//父进程沉睡五秒后读，在这五秒中子进程一瞬间写完，子进程退出，父进程5秒后打印数据
	return 0;
}
#endif
#if 0
//3.读端不读了，读文件描述符关闭，write操作产生信号SIGPIPE（触发异常），可能会导致write进程退出
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
	int fd[2]={0};
	pipe(fd);
	pid_t id=fork();
	if(id==0)//child
	{
		close(fd[0]);
		const char* str="I am child";
		int count=0;
		while(1)
		{
			write(fd[1],str,strlen(str));
			count+=strlen(str);
			cout<<count<<endl;
			sleep(1);
		}
		exit(0);
	}
	else//father
	{
		close(fd[1]);
		char buf[1024];
		while(1)
		{
			sleep(5);
			ssize_t s=read(fd[0],buf,sizeof(buf)-1);
			if(s>0)
			{
				buf[s]=0;
				cout<<buf<<endl;
			}
			else if(s==0)
			{
				cout<<"read file end"<<endl;
				break;
			}
			else 
			{
				cout<<"read file error"<<endl;
				break;
			}
			break;//读一次后不读了，退出
		}
		close(fd[0]);//关掉读端描述符
		int status=0;
		waitpid(id,&status,0);//子进程产生信号，父进程拿到子进程退出信息
		cout<<(status&0x7f)<<endl;//拿到子进程退出信号
	}
	return 0;
}
#endif
//4.写端不写了，写文件描述符也关闭，read返回0（类似于读到文件末尾，写端关闭，文件描述符也关闭，此时读端阻塞就没有意义
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
	int fd[2]={0};
	pipe(fd);
	pid_t id=fork();
	if(id==0)//child
	{
		close(fd[0]);
		const char* str="I am child";
		int count=0;
		while(1)
		{
			write(fd[1],str,strlen(str));
			count+=strlen(str);
			cout<<count<<endl;
			sleep(1);
			close(fd[1]);//关闭写端
			break;
		}
	}
	else//father
	{
		close(fd[1]);//关闭写端
		char buf[1024];
		while(1)
		{
			ssize_t s=read(fd[0],buf,sizeof(buf)-1);
			if(s>0)
			{
				buf[s]=0;
				cout<<buf<<endl;
			}
			else if(s==0)
			{
				cout<<"read file end"<<endl;
				break;
			}
			else
			{
				cout<<"read file error"<<endl;
				break;
			}
		}
		waitpid(id,nullptr,0);
	}
	return 0;
}
