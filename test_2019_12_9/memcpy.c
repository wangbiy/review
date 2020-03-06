#include <stdio.h>
#include <assert.h>
void* my_memcpy(void* dest, const void* src, size_t n)
{
	assert(dest);
	assert(src);
	void* pdest = dest;
	while (--n)
	{
		*(char*)pdest = *(char*)src;
		pdest=((char*)pdest)+1;
		src=((char*)src)+1;
	}
	return dest;
}
int main()
{
	char str1[]="hello";
	char str2[]="world";
	my_memcpy(str1,str2,sizeof(str2)/sizeof(str2[0]));
	printf("%s\n",str1);
	return 0;
}
