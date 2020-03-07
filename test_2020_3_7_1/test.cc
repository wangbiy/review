#include <iostream>
using namespace std;
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#if 0
void* rout(void* arg)
{
	while(1)
	{
		cout<<"I am thread 1:"<<getpid()<<endl;
		sleep(1);
	}
}
//线程控制
int main()
{
	//1.创建线程
	pthread_t tid;
	char* ptr="thread 1";
	int ret=pthread_create(&tid,nullptr,rout,(void*)ptr);
	if(ret!=0)
	{
		cout<<"pthread_create error"<<(char*)rout<<endl;
	}
	while(1)
	{
		cout<<"I am main thread:"<<getpid()<<endl;
		sleep(1);
	}
	return 0;
}
#endif
#if 0
void* rout(void* arg)
{
	while(1)
	{
		srand((unsigned long)time(nullptr));
		cout<<"I am thread1:"<<getpid()<<endl;
		int time=rand()%10;
		sleep(1);
		int a=10/0;//出现异常,主线程没有问题，但是一旦出异常，整个进程都退出，也就是一个线程出异常，各个进程都退出
	}
}
int main()
{
	pthread_t tid;
	pthread_create(&tid,nullptr,rout,(void*)"thread1");
	pthread_create(&tid,nullptr,rout,(void*)"thread2");
	pthread_create(&tid,nullptr,rout,(void*)"thread3");
	pthread_create(&tid,nullptr,rout,(void*)"thread4");
	pthread_create(&tid,nullptr,rout,(void*)"thread5");
	while(1)
	{
		cout<<"I am main thread:"<<getpid()<<endl;
		sleep(1);
	}
	return 0;
}
#endif
#if 0
//线程等待
//在创建好新线程后，必须让主线程去等待新线程，倘若不等待，已经退出的线程的空间没有释放，仍然在进程地址空间内，创建新的线程不会复用刚才退出线程的地址空间，就会造成类似于僵尸进程的问题，造成内存泄漏
void* rout(void* arg)
{
	while(1)
	{
		cout<<"I am thread1:"<<(char*)arg<<endl;
		sleep(1);
	}
}
int main()
{
	pthread_t tid;
	pthread_create(&tid,nullptr,rout,(void*)"thread1");
	cout<<"I am main thread"<<tid<<endl;
	pthread_join(tid,nullptr);//以阻塞方式等待
	return 0;
	return 0;
}
#endif
//线程终止
#if 0
//1.通过return终止
void* rout(void* arg)
{
	while(1)
	{
		cout<<"I am thread 1:"<<(char*)arg<<endl;
		sleep(1);
		break;
	}
	return (void*)11;
}
int main()
{
	pthread_t tid;
	pthread_create(&tid,NULL,rout,(void*)"thread 1");
	cout<<"I am main thread:"<<tid<<endl;
	void* ret;
	pthread_join(tid,&ret);//线程等待，ret保存线程处理函数的返回值
	cout<<"ret:"<<(long)ret<<endl;
	//退出码为11，进程退出，新线程退出导致进程退出，也导致主线程退出户，根本没有返回的机会，线程退出是默认线程正常运行，没有出异常，因为出异常主线程没有办法，主线程已经退出了，只关心结果是否正确，因此线程退出没有办法拿到退出信号，只能返回退出码
	return 0;
}
#endif
#if 0
//2.使用pthread_exit函数退出
void* rout(void* arg)
{
	while(1)
	{
		cout<<"I am thread1:"<<(char*)arg<<endl;
		sleep(1);
		break;
	}
	pthread_exit((void*)3);
}
int main()
{
	pthread_t tid;
	pthread_create(&tid,nullptr,rout,(void*)"thread1");
	cout<<"I am main thread:"<<tid<<endl;
	void* ret;
	pthread_join(tid,&ret);
	cout<<"ret:"<<(long)ret<<endl;
	return 0;
}
#endif
#if 0
#include <string.h>
//线程取消
pthread_t main_id;//主线程id
void* thread_run(void* arg)
{
	int count=5;
	while(count--)
	{
		cout<<"I am a new thread,tid is:"<<pthread_self()<<endl;
		sleep(1);
		int ret=pthread_cancel(main_id);//能不能让新线程取消主线程
		cout<<"ret:"<<ret<<endl;
	}
	pthread_exit((void*)111);
}
int main()
{
	main_id=pthread_self();//主线程id
	pthread_t tid;
	int num =1;
	pthread_create(&tid,nullptr,thread_run,(void*)&num);
	cout<<"main thread get a new thread tid:"<<tid<<endl;
	void* ret;
	pthread_join(tid,&ret);
	cout<<"ret:"<<(long)ret<<endl;
	//得到结论是新线程可以取消主线程，但是进程没有退出，主线程不运行，新线程变成了类似于僵尸进程的状态，因为没有人调用join，最终交给bash回收，如果主线程调用return就代表进程退出，全部退出
	return 0;
}
#endif
//线程分离
#if 0
//新线程创建出之后，主线程阻塞等待，但是此时主线程想要做其他事情，但是线程没有非阻塞轮询，此时就需要用到线程分离，
void* thread_run(void* arg)
{
	pthread_detach(pthread_self());
	int count=5;
	while(count--)
	{
		cout<<"I am a new thread,tid is:"<<pthread_self()<<endl;
		sleep(1);
	}
}
int main()
{
	pthread_t tid;
	int num=1;
	pthread_create(&tid,nullptr,thread_run,(void*)&num);
	sleep(1);//如果没有这个sleep,新线程没有分离，主线程一直在阻塞等待新线程退出
	cout<<"main thread get a new thread tid:"<<tid<<endl;
	int ret=pthread_join(tid,nullptr);//阻塞等待
	cout<<"ret:"<<ret<<endl;
	return 0;
}
#endif
//在创建新线程之后，有两个执行流，如果主线程先运行，主线程立马等待，此时新线程还没有被分离，主线程一直在等待新线程退出，因此还有一种分离方式
void* thread_run(void* arg)
{
	int count=5;
	while(count--)
	{
		cout<<"I am a new thread,tid is:"<<pthread_self()<<endl;
		sleep(1);
	}
}
int main()
{
	pthread_t tid;
	int num=1;
	pthread_create(&tid,nullptr,thread_run,(void*)&num);
	pthread_detach(tid);//由主线程分离新线程
	cout<<"main thread get a new thread tid:"<<tid<<endl;
	int ret=pthread_join(tid,nullptr);
	cout<<ret<<endl;
	return 0;
}
