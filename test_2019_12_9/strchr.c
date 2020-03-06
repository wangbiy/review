#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
char* my_strchr(char* str,char k)
{
	assert(str);
	while(*str!='\0' && *str!=k)
	{
		str++;
	}
	if(*str==k)
		return str;
	return NULL;
}
int main()
{
	char* str="agcnhk";
	char k='a';
	char* ret=my_strchr(str,k);
	printf("%s\n",ret);
	return 0;
}
