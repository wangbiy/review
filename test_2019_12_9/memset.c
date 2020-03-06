#include <stdio.h>
#include <assert.h>
void* my_memset(void* src,int val,size_t count)
{
	assert(src);
	void* ret=src;
	while(count--)
	{
		*(char*)src=(char)val;
		src=(char*)src+1;
	}
	return ret;
}
int main()
{
	char str[]="hello";
	my_memset(str,'*',1);
	printf("%s\n",str);
	return 0;
}
