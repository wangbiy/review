#include <iostream>
using namespace std;
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <queue>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#define NUM 32//表示命令最多有32个
#define MAX 1024
char buff[MAX];//存放命令行的每一个字符
char* argv[NUM];//存放解析后的命令行，每个元素是一个字符指针指向每一个命令字符串
queue<char*> q;//定义一个队列实现管道
void display()
{
	string tips="[XXX@localhost YYY]$";
	cout<<tips;
	fflush(stdout);
	fgets(buff,MAX,stdin);//从标准输入拿到命令行放到buf中
	buff[strlen(buff)-1]=0;//将\n设为0，防止回车之后多出一行
}
//上面已经拿到了命令行每一个字符，然后解析命令行
void analy(char* buf)
{
	int i=0;
	argv[0]=strtok(buf," ");
	while(argv[i]!=nullptr)
	{
		i++;
		argv[i]=strtok(nullptr," ");
	}
}
//解析命令行完成，开始实现管道
queue<char*>& pipe_num()//判断是否有管道符，遇到管道符就置为\0，然后入队，使用时从队列中取出
{
	while(!q.empty())
	{
		q.pop();
	}
	char* ptr=buff;
	q.push(ptr);
	while(*ptr!='\0')
	{
		if(*ptr=='|')
		{
			*ptr='\0';
			ptr++;
			while(*ptr==' ')
				ptr++;
			q.push(ptr);
		}
		ptr++;
	}
	return q;
}
//实现重定向
void diredict(char* buf)
{
	char* ptr=buf;
	char* file=nullptr;//重定向的文件
	int flag=0;//1表示清空重定向，2表示追加重定向
	int fd;
	while(*ptr!='\0')
	{
		if(*ptr=='>')//清空重定向
		{
			*ptr='\0';
			flag=1;
			ptr++;
			//在清空重定向符号前提下，再加一个>就是追加重定向
			if(*ptr=='>')
			{
				flag=2;
				ptr++;
			}
			//然后将>后的空白字符走完，直到文件名的起始位置
			while((*ptr!=' ') && (*ptr!='\0'))
				ptr++;
			file=ptr;//文件名起始位置
			//后面重定向的参数也要加上
			while((*ptr!=' ') && (*ptr!='\0'))
				ptr++;
			*ptr='\0';
		}
		ptr++;
	}
	if(flag==1)//说明是清空重定向
	{
		fd=open(file,O_CREAT|O_WRONLY|O_TRUNC,0644);
		dup2(fd,1);
	}
	else if(flag==2)
	{
		fd=open(file,O_CREAT|O_WRONLY|O_TRUNC,0644);
		dup2(fd,1);//重定向的文件描述符不会随着程序初始化
	}
	close(fd);
}
//进程替换
void do_fork(queue<char*>& q)
{
	while(!q.empty())
	{
		pid_t id=fork();
		if(id<0)
		{
			cout<<"fork error"<<endl;
		}
		else if(id==0)//child
		{
			char* temp=q.front();
			diredict(temp);
			analy(temp);
			execvp(argv[0],argv);
		}
		else//father
		{
			waitpid(id,nullptr,0);
		}
		q.pop();
	}
}
int main()
{
	while(1)
	{
		display();
		queue<char*>& q_pipe=pipe_num();
		do_fork(q_pipe);
		sleep(1);
	}
	return 0;
}
