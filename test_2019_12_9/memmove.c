#include <stdio.h>
#include <assert.h>
void* my_memmove(void* dest,void* src,size_t n)
{
	assert(dest);
	assert(src);
	void* pdest=dest;
	if(pdest<src)
	{
		while(n--)
		{
			*(char*)pdest=*(char*)src;
			pdest=((char*)pdest)+1;
			src=((char*)src)+1;
		}
		return dest;
	}
	else
	{
		while(n--)
		{
			*((char*)pdest+n)=*((char*)src+n);
		}
		return dest;
	}
}
int main()
{
	char str1[]="hello world";
	char str2[]="hahahahahahaha";
	my_memmove(str1,str2,sizeof(str2)/sizeof(str2[0]));
	printf("%s\n",str1);
	return 0;

}
