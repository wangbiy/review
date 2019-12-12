#pragma once
template<class T>
class SeqList
{
	public:
		SeqList()
			:_arr(new T[3])
			 ,_capacity(3)
			 ,_size(0)
	{}
		SeqList(T* arr,int size)
			:_arr(new T[size])
			 ,_capacity(size)
			 ,_size(size)
		{
			for(int i=0;i<size;++i)
			{
				_arr[i]=arr[i];
			}
		}
		~SeqList()
		{
			if(_arr)
			{
				delete[]_arr;
				_arr=nullptr;
				_capacity=0;
				_size=0;
			}
		}
		SeqList(const SeqList& s)
			:_arr(new T[s._size])
			 ,_capacity(s._capacity)
			 ,_size(s._size)
		{
			for(int i=0;i<s._size;++i)
			{
				_arr[i]=s._arr[i];
			}
		}
		SeqList& operator=(const SeqList& s)
		{
			if(this!=&s)
			{
				for(int i=0;i<s._size;++i)
				{
					_arr[i]=s._arr[i];
				}
				_capacity=s._capacity;
				-size=s._size;
				return *this;
			}
		}
		void show();//打印
		void PushBack(const T& data);
		void PopBack();
		void PushFront(const T& data);
		void PopFront();
		bool Find(const T& data);
		void Insert(int pos,const T& data);//任意位置插入
		void Erase(int pos);//任意位置删除
		int SeqListCapacity();
		int SeqListSize();
		bool Empty();
		T& SeqListFront();//返回第一个元素
		T& SeqListBack();//返回最后一个元素
		void SeqListRemove(const T& data);//移除第一个为data的元素
		void RemoveAll(const T& data);//移除所有为data的元素
		void SeqListSort();//排序
	public:
		T* _arr;
		int _capacity;
		int _size;
};

