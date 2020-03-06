#include <stdio.h>
#include <assert.h>
int my_strncmp(const char* s1,const char* s2,int n)
{
	assert(s1);
	assert(s2);
	while(n--)
	{
		if(*s1==*s2)
		{
			s1++;
			s2++;
		}
		else
			return *s2-*s1;
	}
}
int main()
{
	char str1[]="hello world1";
	char str2[]="hello world!";
	int ret=my_strncmp(str1,str2,11);
	if(ret==0)
		printf("相同\n");
	else
		printf("不相同\n");
	return 0;
}
