//通过系统调用获取进程标识符
//#include <stdio.h>
//#include <unistd.h>
//int main()
//{
//	printf("pid:%d\n",getpid());//获取进程标识符
//	printf("ppid:%d\n",getppid());//获取父进程标识符
//
//	return 0;
//}
//通过fork创建子进程
//#include <iostream>
//using namespace std;
//#include <unistd.h>
//int main()
//{
//	cout<<"before"<<endl;
//	fork();
//	cout<<"after"<<endl;
//	cout<<"I am a process"<<"pid:"<<getpid()<<" "<<"ppid:"<<getppid()<<endl;
//	sleep(1);
//	return 0;
//}
//验证僵尸进程
//#include <iostream>
//using namespace std;
//#include <unistd.h>
//int main()
//{
//	pid_t id=fork();
//	if(id<0)
//	{
//		perror("fork");
//		return 1;
//	}
//	else if(id>0)//parent
//	{
//		cout<<"parent is sleeping"<<getpid()<<endl;
//		sleep(30);
//	}
//	else//child
//	{
//		cout<<"child is sleeping"<<getpid()<<endl;
//		sleep(5);
//		exit(EXIT_SUCCESS);
//	}
//	return 0;
//}
//孤儿进程
//#include <iostream>
//using namespace std;
//#include <unistd.h>
//int main()
//{
//	pid_t id=fork();
//	if(id==0)//child
//	{
//		cout<<"child ppid:"<<" "<<getppid()<<" "<<"child pid:"<<" "<<getpid()<<endl;
//		sleep(30);
//		cout<<"child ppid:"<<" "<<getppid()<<" "<<"child pid:"<<" "<<getpid()<<endl;
//	}
//	else
//	{
//		sleep(5);
//		cout<<"parent ppid"<<" "<<getppid()<<"parent pid:"<<" "<<getpid()<<endl;
//	}
//
//}
//环境变量
//#include <iostream>
//using namespace std;
//命令行第三个参数获取环境变量
//int main(int argc,char* argv[],char* env[])
//{
//	for(int i=0;env[i];++i)
//	{
//		cout<<i<<":"<<env[i]<<endl;
//	}
//	return 0;
//}
//通过第三方指针environ获取环境变量
//int main()
//{
//	extern char**environ;
//	for(int i=0;environ[i];++i)
//	{
//		cout<<i<<":"<<environ[i]<<endl;
//	}
//	return 0;
//}
//通过系统调用获取和设置环境变量
//int main()
//{
//	cout<<getenv("PATH")<<endl;
//	return 0;
//}
//程序地址空间
#include <iostream>
using namespace std;
#include <unistd.h>
int g_val=100;
int main()
{
	pid_t id=fork();
	if(id==0)//child
	{
		sleep(1);
		g_val=200;
		cout<<"child:"<<g_val<<" "<<&g_val<<endl;
	}
	else
	{
		sleep(3);
		cout<<"father:"<<g_val<<" "<<&g_val<<endl;
	}
	return 0;
}
