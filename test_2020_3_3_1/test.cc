#include <iostream>
using namespace std;
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
//int main()
//{
//	cout<<"hello world"<<endl;
//	return 0;//退出码是0
//}
//int main()
//{
//	cout<<"hello world"<<endl;
//	exit(123);//表示退出码是123
	//进程等待
	//wait方法
//	pid_t id=fork();
//	if(id==0)//child
//	{
//		cout<<"I am a child"<<endl;
//		sleep(5);
//		exit(1);
//	}
//	else//father
//	{
//		wait(NULL);//父进程等待
//		cout<<"I am parent"<<endl;
//	}
	//waitpid方法
//	pid_t id=fork();
//	if(id==0)//child
//	{
//		cout<<"I am child"<<endl;
//		sleep(5);
//		exit(13);
//	}
//	else//father
//	{
//		cout<<"father"<<endl;
//		int status;
//		int ret=waitpid(id,&status,0);//wait和waitpid都有一个status参数，它是一个输出型参数，由操作系统提供
//		if(ret<0)
//		{
//			cout<<"wait error"<<endl;
//		}
//		else
//		{
//			cout<<"wait sucess...."<<endl;
//		}
//		sleep(5);
//	}
//	return 0;
//}
//int main()
//{
//	pid_t id=fork();
//	if(id==0)
//	{
//		cout<<"I am child"<<endl;
//		sleep(5);
//		exit(13);
//	}
//	else//father
//	{
//		cout<<"I am father"<<endl;
//		int status =0;
//		sleep(10);
//		int ret=waitpid(id,&status,0);
//		if(ret<0)
//		{
//			cout<<"wait error"<<endl;
//		}
//		else
//		{
//			cout<<"wait success"<<ret<<endl;
//			cout<<"exit status"<<((status>>8)&0xFF)<<endl;//是否core dump
//			cout<<"exit signals"<<(status&0x7f)<<endl;//终止信号
//		}
//		sleep(5);
//	}
//	return 0;
//}
//进程程序替换
int main()
{
	//execl函数
//	execl("/usr/bin/ls","ls","-a","-l","-i",NULL);//表示用ls进程替换当前进程
	//execlp函数
//	execlp("ls","-a","-l","-i",NULL);
	//execle函数
//	char* const envp[]={"PATH=/bin:/usr/bin","TREM=console",NULL};//环境变量
//	execle("usr/bin/ps","ps","-ef",envp);
	//execv函数
//	char* argv[]={"ls","-a","-l","-i",NULL};
//	execv("/usr/bin/ls",argv);
//	execvp函数
//	execve函数
	return 0;
}
