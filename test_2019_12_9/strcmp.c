#include <stdio.h>
#include <assert.h>
int my_strcmp(const char* s1,const char* s2)
{
	assert(s1);
	assert(s2);
	while(*s1==*s2)
	{
		if(*s1=='\0')
			return 0;
		s1++;
		s2++;
	}
	return *s2-*s1;
}
int main()
{
	char* str1="abcv";
	char* str2="abcv";
	int ret=my_strcmp(str1,str2);
	if(ret==0)
		printf("相同\n");
	else
		printf("不相同\n");
	return 0;
}
