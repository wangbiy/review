#include <iostream>
using namespace std;
#include <pthread.h>
#include <unistd.h>
#include <queue>
//线程池
class Task//定义任务两数相加类
{
	private:
		int x;
		int y;
	public:
		Task()
		{}
		~Task()
		{}
		void SetData(int _x,int _y)
		{
			x=_x;
			y=_y;
		}
		int Run()
		{
			return x+y;
		}
};
class ThreadPool//线程池类
{
	private:
		int num;//有多少个线程
		queue<Task> q;//任务队列
		pthread_mutex_t lock;//互斥量
		pthread_cond_t cond;//条件变量
	public:
		ThreadPool(int _num=6)
			:num(_num)
		{
			pthread_mutex_init(&lock,nullptr);
			pthread_cond_init(&cond,nullptr);
		}
		~ThreadPool()
		{
			pthread_mutex_destroy(&lock);
			pthread_cond_destroy(&cond);
		}
		static void* HandlerTask(void* arg)//在类内使用需要将线程处理函数设置为static的，因为此时传的实参是this，如果是非static的成员函数，隐含的传入了this指针，不满足回调机制，因此是static的成员函数
		{
			pthread_detach(pthread_self());//新线程分离
			ThreadPool* tp=(ThreadPool*)arg;
			for(;;)
			{
				tp->LockQueue();//加锁
				if(tp->QueueIsEmpty())//如果任务队列是空，则线程等待直到有任务到来
					tp->ThreadWait();
				//走到这里说明任务队列不为空，拿出任务
				Task t;
				tp->PopTask(t);
				tp->UnlockQueue();
				//开始处理任务，拿出的任务不在临界资源中，不用在锁机制中
				int result=t.Run();
				cout<<"Thread:"<<pthread_self()<<"result:"<<result<<endl;
			}
		}
		void InitThreadPool()
		{
			pthread_t tid;
			for(int i=0;i<num;++i)
			{
				pthread_create(&tid,nullptr,HandlerTask,(void*)this);//创建num个线程

			}
		}
		void AddTask(Task& t)//添加任务
		{
			LockQueue();
			PushTask(t);
			UnlockQueue();
			NotifyThread();//添加任务之后通知线程
		}
	private:
		void LockQueue()
		{
			pthread_mutex_lock(&lock);
		}
		void UnlockQueue()
		{
			pthread_mutex_unlock(&lock);
		}
		bool QueueIsEmpty()
		{
			return (q.size()==0 ? true:false);
		}
		void ThreadWait()
		{
			pthread_cond_wait(&cond,&lock);
		}
		void PushTask(Task& t)
		{
			q.push(t);
		}
		void PopTask(Task& t)
		{
			t=q.front();
			q.pop();
		}
		void NotifyThread()
		{
			pthread_cond_signal(&cond);
		}

};
int main()
{
	ThreadPool* tp=new ThreadPool(5);
	tp->InitThreadPool();
	int count=0;
	for(;;)
	{
		int x=count%1000+100;
		int y=count%2000+300;
		count++;
		Task t;
		t.SetData(x,y);
		tp->AddTask(t);
		sleep(1);
	}
	delete tp;
	return 0;
}
