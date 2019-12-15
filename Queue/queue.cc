#include "queue.hpp"
void TestQueue()
{
	Queue<int> q1;
	q1.QueuePush(1);
	q1.QueuePush(2);
	q1.QueuePush(3);
	q1.QueuePush(4);
	q1.QueuePop();
	q1.QueuePop();
	q1.QueuePrint();
	int data=q1.QueueFront();
	cout<<data<<endl;
	data=q1.QueueBack();
	cout<<data<<endl;
	int size=q1.QueueSize();
	cout<<size<<endl;
	q1.Empty();
}
int main()
{
	TestQueue();
	return 0;
}
