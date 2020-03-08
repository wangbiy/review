#include <iostream>
using namespace std;
//单例模式
#if 0
//饿汉模式：单例类在创建单例对象时就new出来对象空间，优化服务器的启动速度
class Singleton
{
	public:
		static Singleton& GetInstrance()
		{
			return m_ins;
		}
	private:
		Singleton()
		{}
		static Singleton m_ins;
		Singleton(const Singleton&)=delete;
		Singleton& operator=(Singleton const&)=delete;
};
Singleton Singleton:: m_ins;//初始化
int main()
{
	Singleton& s=Singleton::GetInstrance();
	return 0;
}
#endif
//懒汉模式
#include <mutex>
class Singleton
{
	public:
		static volatile Singleton* GetInstrance()
		{
			if(nullptr==m_ins)
			{
				m_mutex.lock();//加锁
				if(nullptr==m_ins)//若为空，说明是第一次调用
					m_ins=new Singleton;
				m_mutex.unlock();//解锁
			}
			return m_ins;
		}
		class GC
		{
			public:
				~GC()
				{
					if(m_ins)
					{
						delete m_ins;
						m_ins=nullptr;
					}
				}
		};//内嵌垃圾回收类
	private:
		Singleton()
		{}
		Singleton(const Singleton&)=delete;
		static volatile Singleton* m_ins;
		static mutex m_mutex;
		static GC m_gc;
};
volatile Singleton* Singleton::m_ins=nullptr;
mutex Singleton::m_mutex;
Singleton:: GC m_gc;
int main()
{
	volatile Singleton* s = Singleton::GetInstrance();
	return 0;
}
