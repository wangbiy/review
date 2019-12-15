#include "stack.hpp"
void TestStack()
{
	Stack<int> s1;
	Stack<int> s2(s1);
	s1.StackPush(1);
	s1.StackPush(2);
	s1.StackPush(3);
	s1.StackPop();
	s1.StackPrint();
	int top=s1.StackTop();
	cout<<top<<endl;
	int size=s1.StackSize();
	cout<<size<<endl;
	s1.Empty();
}
int main()
{
	TestStack();
	return 0;
}
