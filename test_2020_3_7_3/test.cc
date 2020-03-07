#include <iostream>
using namespace std;
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <queue>
#include <time.h>
#include <semaphore.h>
#if 0
//条件变量：由于互斥可能会产生饥饿问题，所以需要同步，在数据安全下，让线程能够按照特定顺序访问临界资源，从而避免饥饿问题当一个线程互斥地访问某个变量时，可能发现在其他线程改变状态之前，他什么也做不了，例如一个线程访问队列时，发现队列为空，他只能等待，直到其他进程将一个结点添加到队列中
pthread_mutex_t lock;//互斥量
pthread_cond_t cond;//条件变量
void* Wait(void* arg)
{
	while(1)
	{
		pthread_cond_wait(&cond,&lock);
		cout<<"active";
	}
}
void* Signal(void* arg)
{
	pthread_cond_signal(&cond);//唤醒
	sleep(1);
}
int main()
{
	pthread_t t1,t2;
	pthread_cond_init(&cond,nullptr);//初始化条件变量
	pthread_mutex_init(&lock,nullptr);//初始化互斥量
	pthread_create(&t1,nullptr,Wait,nullptr);
	pthread_create(&t2,nullptr,Signal,nullptr);

	pthread_join(t1,nullptr);
	pthread_join(t2,nullptr);
	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&cond);
}
#endif
#if 0
//生产者消费者模型：生产者与生产者之间是互斥关系，消费者和消费者之间是互斥关系，生产者和消费者是互斥和同步关系
class BlockQueue//阻塞队列
{
	private:
		queue<int> q;
		int cap;//容量
		pthread_mutex_t lock;//互斥量
		pthread_cond_t c_cond;//消费者条件变量
		pthread_cond_t p_cond;//生产者条件变量
	private:
		void LockQueue()
		{
			pthread_mutex_lock(&lock);
		}
		void UnlockQueue()
		{
			pthread_mutex_unlock(&lock);
		}
		void ProducterWait()
		{
			cout<<"Producter wait"<<endl;
			pthread_cond_wait(&p_cond,&lock);
		}
		void ConsumerWait()
		{
			cout<<"Cosumer wait"<<endl;
			pthread_cond_wait(&c_cond,&lock);
		}
		void SignalProducter()
		{
			cout<<"signal producter"<<endl;
			pthread_cond_signal(&p_cond);
		}
		void SignalConsumer()
		{
			cout<<"signal consumer"<<endl;
			pthread_cond_signal(&c_cond);
		}
		bool QueueIsFull()
		{
			return (q.size()==cap ? true:false);
		}
		bool QueueIsEmpty()
		{
			return (q.size()==0 ? true:false);
		}
	public:
		BlockQueue(int _cap=32)//构造函数
			:cap(_cap)
		{
			pthread_mutex_init(&lock,nullptr);
			pthread_cond_init(&c_cond,nullptr);
			pthread_cond_init(&p_cond,nullptr);
		}
		~BlockQueue()
		{
			pthread_mutex_destroy(&lock);
			pthread_cond_destroy(&c_cond);
			pthread_cond_destroy(&p_cond);
		}
		//生产
		void PushData(const int& data)
		{
			LockQueue();//加锁
			if(QueueIsFull())//判断队列是否满了
			{
				cout<<"queue is full"<<endl;
				SignalConsumer();//通知消费者消费
				ProducterWait();//生产者阻塞
			}
			//队列没有满
			q.push(data);
			UnlockQueue();//解锁
		}
		//消费
		void PopData(int& out)
		{
			LockQueue();
			if(QueueIsEmpty())//如果队列为空
			{
				cout<<"queue is empty"<<endl;
				SignalProducter();//通知生产者生产
				ConsumerWait();//消费者阻塞
			}
			out=q.front();
			q.pop();
			UnlockQueue();
		}
};
void* Producter(void* arg)
{
	BlockQueue* bq=(BlockQueue*)arg;
	while(1)
	{
		int data=rand()%10+1;//随机生成一个数据
		bq->PushData(data);//放进阻塞队列
		cout<<"product data is:"<<data<<endl;
		sleep(1);//让生产者慢一点
	}
}
void* Consumer(void* arg)
{
	BlockQueue* bq=(BlockQueue*)arg;
	int data;
	while(1)
	{
		bq->PopData(data);
		cout<<"consum data is:"<<data<<endl;
	}
}
int main()
{
	srand((unsigned long)time(nullptr));
	BlockQueue* bq=new BlockQueue(4);//分配4个空间
	pthread_t c,p;

	pthread_create(&p,nullptr,Producter,(void*)bq);
	pthread_create(&c,nullptr,Consumer,(void*)bq);

	pthread_join(p,nullptr);
	pthread_join(c,nullptr);
	return 0;
}
#endif
//POSIX信号量
//它与system V信号量一样都是用来实现同步操作的，达到无冲突的访问共享资源的目的，但是POSIX可以用于线程间同步，将信号量当成一个计数器，当值为1时代表有一份资源可以使用，有人申请这份资源时，值-1，当值为0时，其它线程想继续申请这份资源，会被挂起放入等待队列
//基于环形队列的单消费者单生产者模型
class RingQueue
{
	private:
		vector<int> buf;//使用顺序表表示环形队列
		int cap;
		sem_t sem_blank;//空格计数（信号量）
		sem_t sem_data;//数据块计数
		int c_step;//消费者步数
		int p_step;//生产者步数
	private:
		void P(sem_t& s)//等待信号量
		{
			sem_wait(&s);
		}
		void V(sem_t& s)//发布信号量
		{
			sem_post(&s);
		}
	public:
		RingQueue(int _cap=1024)
			:cap(_cap)
			 ,buf(_cap)
		{
			c_step=p_step=0;
			sem_init(&sem_blank,0,cap);
			sem_init(&sem_data,0,0);//一开始没有数据
		}
		~RingQueue()
		{
			sem_destroy(&sem_blank);
			sem_destroy(&sem_data);
		}
		//添加数据
		void PushData(const int& data)
		{
			P(sem_blank);//申请数据资源，即减少空格数目
			buf[p_step]=data;
			p_step++;
			p_step%=cap;
			V(sem_data);//归还数据资源，增加数据数目
		}
		void PopData(int& data)
		{
			P(sem_data);//申请空格资源，即减少数据数目
			data=buf[c_step];
			c_step++;
			c_step%=cap;
			V(sem_blank);//归还空格资源，即增加空格数目
		}
};
void* Producter(void* arg)
{
	RingQueue* rq=(RingQueue*)arg;
	while(1)
	{
		int data=rand()%10+1;
		rq->PushData(data);
		cout<<"product data is"<<data<<endl;
	}
}
void* Consumer(void* arg)
{
	RingQueue* rq=(RingQueue*)arg;
	int data;
	while(1)
	{
		rq->PopData(data);
		cout<<"consume data is:"<<data<<endl;
		sleep(data%5+1);//让消费慢一点
	}
}
int main()
{
	srand((unsigned long)time(nullptr));
	RingQueue* rq=new RingQueue(8);
	pthread_t c,p;
	pthread_create(&c,nullptr,Consumer,(void*)rq);
	pthread_create(&p,nullptr,Producter,(void*)rq);

	pthread_join(c,nullptr);
	pthread_join(p,nullptr);
	delete rq;
}
