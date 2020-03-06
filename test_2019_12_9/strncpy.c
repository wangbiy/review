#include <stdio.h>
#include <assert.h>
char* my_strncpy(char* dest,const char* src,int n)
{
	assert(dest);
	assert(src);
	char* pdest=dest;
	const char* psrc=src;
	while(n--)
	{
		*pdest++=*psrc++;
		if(*psrc=='\0')
		{
			*pdest='\0';
			break;
		}
	}
	return dest;
}
int main()
{
	char dest[]="agcb";
	char src[]="bhklwww";
	my_strncpy(dest,src,4);
	printf("%s",dest);
	printf("\n");
	return 0;
}
