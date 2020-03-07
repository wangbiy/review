#include <iostream>
using namespace std;
#include <pthread.h>
#include <unistd.h>
//线程互斥
#if 0
//实现售票系统
int tickets=200;
void* GetTicket(void* arg)
{
	while(1)
	{
		if(tickets>0)//有票
		{
			usleep(100000);
			cout<<"get a ticket no is:"<<(tickets--)<<endl;
		}
		else
		{
			cout<<(char*)arg<<"--------quit"<<endl;
			break;
		}
	}
	pthread_exit((void*)0);
}
int main()
{
	pthread_t tid1,tid2,tid3,tid4;
	pthread_create(&tid1,nullptr,GetTicket,(void*)"thread1");
	pthread_create(&tid2,nullptr,GetTicket,(void*)"thread2");
	pthread_create(&tid3,nullptr,GetTicket,(void*)"thread3");
	pthread_create(&tid4,nullptr,GetTicket,(void*)"thread4");


	pthread_join(tid1,nullptr);
	pthread_join(tid2,nullptr);
	pthread_join(tid3,nullptr);
	pthread_join(tid4,nullptr);
	return 0;
}
//这样做到结果是一共只有200张票，但是卖出去的票比200还多，因为可能有多个线程同时访问tickets这个临界资源，再加上tickets--不是原子操作，因此要解决这个问题，必须让代码有互斥行为；当多个线程同时要求执行临界区的代码，并且临界区没有线程在执行，只允许一个线程进入临界区，如果线程不在临界区执行，那么该线程不能阻止其他线程进入临界区，因此需要互斥锁
#endif
//互斥锁
//还是上述的售票系统加锁
int tickets=200;
pthread_mutex_t lock;//创建锁
void* GetTicket(void* arg)
{
	while(1)
	{
		pthread_mutex_lock(&lock);//加锁
		if(tickets>0)
		{
			usleep(100000);
			cout<<"get a ticket no is:"<<tickets--<<endl;
			pthread_mutex_unlock(&lock);
		}
		else
		{
			cout<<(char*)arg<<"---------quit"<<endl;
			pthread_mutex_unlock(&lock);
			break;
		}
	}
	pthread_exit((void*)0);
}
int main()
{
	pthread_mutex_init(&lock,nullptr);//初始化互斥量
	pthread_t tid1,tid2,tid3,tid4;
	pthread_create(&tid1,nullptr,GetTicket,(void*)"thread1");
	pthread_create(&tid2,nullptr,GetTicket,(void*)"thread2");
	pthread_create(&tid3,nullptr,GetTicket,(void*)"thread3");
	pthread_create(&tid4,nullptr,GetTicket,(void*)"thread4");
	
	pthread_join(tid1,nullptr);
	pthread_join(tid2,nullptr);
	pthread_join(tid3,nullptr);
	pthread_join(tid4,nullptr);
	pthread_mutex_destroy(&lock);//销毁
	return 0;
}

