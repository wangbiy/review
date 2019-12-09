#include <stdio.h>
#include <assert.h>
char* my_strcpy(char* dest,const char* src)
{
	assert(dest);
	assert(src);
	char* pdest=dest;
	const char* psrc=src;
	while(*pdest++=*psrc++)
	{
		;
	}
	return dest;
}
int main()
{
	char src[]="agcbvk";
	char dest[]={0};
	char* ret=my_strcpy(dest,src);
	printf("%s",ret);
	printf("\n");
	return 0;
}
