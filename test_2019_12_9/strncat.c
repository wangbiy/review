#include <stdio.h>
#include <assert.h>
char* my_strncat(char* dest,const char* src,int n)
{
	assert(dest);
	assert(src);
	char* pdest=dest;
	const char* psrc=src;
	while(*pdest)
	{
		pdest++;
	}
	while(n--)
	{
		*pdest++=*psrc++;
	}
	*pdest='\0';
	return dest;
}
int main()
{
	char dest[]="hello ";
	char src[]="world,haha";
	my_strncat(dest,src,5);
	printf("%s\n",dest);
	return 0;
}
