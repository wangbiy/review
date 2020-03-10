#pragma once
#include <iostream>
using namespace std;
#include <pthread.h>
#include <queue>
#include <map>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>
map<string,string> dict= {
	{"apple","苹果"},
	{"banana","香蕉"},
	{"orange","橘子"}
};//实现线程池版本的英译汉服务器
class Task//任务是进行单词的翻译
{
	private:
		int fd;
	public:
		Task()
		{}
		Task(int _fd)
			:fd(_fd)
		{}
		void Run()
		{
			string key;
			char buf[1024];
			while(1)
			{
				ssize_t s=recv(fd,buf,sizeof(buf)-1,0);
				if(s>0)
				{
					buf[s]=0;
					cout<<"client#"<<buf<<endl;
					key=buf;
				}
				string value;
				auto it=dict.find(key);
				if(it!=dict.end())
				{
					value=it->second;
				}
				else
					value="unknow";
				send(fd,value.c_str(),value.size(),0);
			}
			close(fd);
		}
};
class ThreadPool
{
	private:
		int num;//创建多少个线程
		queue<Task> q;//任务队列
		pthread_mutex_t lock;
		pthread_cond_t cond;
	public:
		ThreadPool(int _num=5)//默认创建5个线程
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
		static void* ThreadRun(void* arg)
		{
			ThreadPool* self=(ThreadPool*)arg;
			pthread_detach(pthread_self());//线程分离
			for(;;)
			{
				self->LockQueue();//加锁
				while(self->QueueIsEmpty())//如果队列一直是空，就要进行阻塞等待，直到有任务来临
				{
					self->ThreadWait();
				}
				//有任务，拿出任务进行处理
				Task t=self->PopTask();
				self->UnlockQueue();//解锁进行处理任务
				t.Run();
			}
		}
		void InitPthreadPool()
		{
			pthread_t tid;
			for(int i=0;i<num;++i)
			{
				pthread_create(&tid,nullptr,ThreadRun,(void*)this);
			}
		}
		void PushTask(Task& t)
		{
			for(;;)
			{
				LockQueue();
				q.push(t);
				UnlockQueue();
				ThreadSingle();
			}
		}
		Task PopTask()
		{
			//这里不用加锁解锁，因为在线程处理汉纳树中拿出任务时已经进行了加锁解锁
			Task t=q.front();
			q.pop();
			return t;
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
		void ThreadWait()
		{
			pthread_cond_wait(&cond,&lock);
		}
		void ThreadSingle()
		{
			pthread_cond_signal(&cond);
		}
		bool QueueIsEmpty()
		{
			return (q.size()==0 ? true:false);
		}
};
