#include <iostream>
using namespace std;
#include <signal.h>
#include <unistd.h>
#if 0
//信号的捕捉
void handler(int signo)
{
	cout<<"catch signal,signo:"<<signo<<endl;
}
int main()
{
	signal(2,handler);//修改信号行为
	while(1)
	{
		cout<<"I am a process"<<endl;
		sleep(1);
	}

	return 0;
}
#endif
//信号的生命周期
//信号的产生
//1.硬件产生：就是在终端上按ctrl+c、ctrl+z等
//2.软件产生：第一种是kill -signum pid表示给指定进程发送指定信号，例如kill -9 pid表示个指定进程发送强制杀死信号
//第二种是调用系统函数向进程发信号
#if 0
//kill函数
int main()
{
	kill(getpid(),3);//给当前进程发送3号信号
	while(1)
	{
		cout<<"----------"<<endl;
	}
	return 0;
}
#endif
#if 0
//raise函数
int main()
{
	raise(SIGQUIT);
	while(1)
	{
		cout<<"-----------------"<<endl;
	}

	return 0;
}
#endif
//abort函数：表示引发不正常的终止
#if 0
int main()
{
	abort();
	while(1)
	{
		cout<<"---------------"<<endl;
	}
	return 0;
}
#endif
#if 0
//alarm函数：定时器，表示调用这个函数，等若干秒后给进程发送SIGALRM信号
int main()
{
	alarm(2);//等2秒
	while(1)
	{
		cout<<"-------------------"<<endl;
	}
	return 0;
}
#endif
//信号捕捉
#if 0
void handler(int signo)
{
	cout<<"catch a sig:"<<signo<<endl;
}
int main()
{
	signal(2,handler);
	while(1);
	return 0;
}
#endif
#if 0
//模拟野指针
int main()
{
	sleep(1);
	int* p=nullptr;
	*p=100;
	return 0;
}
#endif
#if 0
//捕捉到11号信号
void handler(int signo)
{
	cout<<"catch a sig:"<<signo<<endl;
	exit(1);
}
int main()
{
	int i=1;
	while(i<=31)
	{
		signal(i++,handler);
	}
	int* p=nullptr;
	*p=100;
	return 0;
}
#endif
//信号的阻塞
//sigprocmask:读取或者更改进程的信号屏蔽字
//sigpending:读取当前进程的未决信号集
#if 0
void show(sigset_t* pending)//遍历位图，一旦产生2号信号输出1
{
	for(int i=1;i<=31;++i)
	{
		if(sigismember(pending,i))//判断是否是2号信号
			cout<<"1";
		else
			cout<<"0";
	}
	cout<<endl;
}
int main()
{
	sigset_t set,oset;//屏蔽2号信号，获取当前pending信号，pending为000000...，然后解除阻塞
	sigemptyset(&set);
	sigemptyset(&oset);
	sigaddset(&set,2);//将2号信号添加到set中
	sigprocmask(SIG_SETMASK,&set,&oset);//更改信号屏蔽字为set所指向的2号信号，就是屏蔽了2号信号
	while(1)
	{
		sigset_t pending;
		sigemptyset(&pending);//初始化未决信号集
		sigpending(&pending);//读取当前未决信号集
		show(&pending);//打印pending
		sleep(1);
	}
	return 0;
}
#endif
#if 0
void show(sigset_t* pending)
{
	for(int i=1;i<=31;++i)
	{
		if(sigismember(pending,i))//如果是2号信号和3号信号
			cout<<"1";
		else
			cout<<"0";
	}
	cout<<endl;
}
int main()
{
	sigset_t set,oset;
	sigemptyset(&set);//初始化
	sigemptyset(&oset);
	sigaddset(&set,2);//将2号信号添加到set中
	sigaddset(&set,3);//将3号信号添加到set中
	sigprocmask(SIG_SETMASK,&set,&oset);
	int count=10;
	while(1)
	{
		sigset_t pending;
		sigemptyset(&pending);//初始化
		sigpending(&pending);//获取未决信号集
		show(&pending);
		sleep(1);
		//恢复，10秒后恢复信号，然后递达
		if(count--<=0)
		{
			cout<<"恢复signal"<<endl;
			sigprocmask(SIG_SETMASK,&oset,nullptr);//恢复成阻塞
		}
	}
	return 0;
}
#endif
#if 0
//volitile关键字:保存内存的可见性，防止变量被过度优化，每次从内存中重新获取变量的数据，修饰的这个变量必须在真实的内存中操作
volatile bool quit=false;//被过度优化，放在了寄存器中，加上volatile关键字
void handler(int signo)
{
	switch(signo)
	{
		case 2:
			quit=true;
			cout<<"catch signal"<<signo<<endl;
			break;
		default:
			break;
	}
}
int main()
{
	signal(2,handler);
	while(!quit)
	{
		cout<<"while quit"<<endl;
	}
	return 0;
}
#endif
//SIGCHLD信号
//进程等待中使用wait或者waitpid函数来处理僵尸进程，父进程要么阻塞等待子进程退出，要么非阻塞轮询是否有子进程结束等待清理，其实，子进程在终止时会向父进程发送SIGCHLD信号，这个信号的默认处理动作是忽略，导致父进程无法及时处理，因此只有使用进程等待才可以，父进程知道什么时候信号到来了，然后调用wait函数或者waitpid函数，则不需要继续等待，父进程可以自定义SIGCHLD信号的处理函数，父进程只需要处理自己的工作，不必关心子进程，子进程在退出时会通知父进程，父进程在信号处理函数中调用wait函数或者waitpid函数
//SIGCHLD信号是非可靠信号，可能会造成信号丢失（因为它在已经注册的情况下就不会再注册了），多个子进程同时退出，只注册了一次信号，剩下的就会变成僵尸进程，因此最好在一次回调函数中就能将所有的僵尸进程都处理掉，即循环调用waitpid函数，直到没有子进程才退出信号回调函数
#include <sys/wait.h>
#include <sys/types.h>
void handler(int signo)
{
	pid_t id;
	while((id=waitpid(-1,nullptr,WNOHANG))>0)
	{
		cout<<"wait child success"<<id<<endl;
	}
	cout<<"child is quit"<<getpid()<<endl;
}
int main()
{
	signal(SIGCHLD,handler);
	pid_t id=fork();
	if(id==0)//child
	{
		cout<<"child id"<<getpid()<<endl;
		sleep(3);
		exit(1);
	}
	else//father
	{
		while(1)
		{
			cout<<"father is doing something"<<getpid()<<endl;
			sleep(1);
		}
	}
}
