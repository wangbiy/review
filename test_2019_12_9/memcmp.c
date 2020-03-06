#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
int my_memcmp(void* str1,void* str2,size_t n)
{
	assert(str1);
	assert(str2);
	char* dest=(char*)str1;
	char* src=(char*)str2;
	while(n && *dest==*src)
	{
		n--;
		dest++;
		src++;
	}
	if(n==0)
		return 0;
	return *dest-*src;
}
int main()
{
	char str1[]="hello world";
	char str2[]="hello world";
	int ret=my_memcmp(str1,str2,12);
	if(ret==0)
		printf("相同\n");
	else
		printf("不相同\n");
	return 0;
}
