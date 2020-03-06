#include <stdio.h>
#include <assert.h>
char* my_strcat(char* dest,const char* src)
{
	assert(dest);
	assert(src);
	char* pdest=dest;
	const char* psrc=src;
	while(*pdest)
	{
		pdest++;
	}
	while(*pdest++ = *psrc++)
	{
		;
	}
	*pdest='\0';
	return dest;
}
int main()
{
	char dest[]="abc";
	char src[]="defgh";
	my_strcat(dest,src);
	printf("%s",dest);
	printf("\n");
	return 0;
}
