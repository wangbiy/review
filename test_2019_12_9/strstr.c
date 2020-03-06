#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
char* my_strstr(char* str1,char* str2)
{
	assert(str1);
	assert(str2);
	char* s1=str1;
	char* s2=str2;
	char* cur=str1;
	while(*cur)
	{
		s1=cur;
		s2=str2;
		while(s1 && s2 && *s1==*s2)
		{
			s1++;
		    s2++;	
		}
		if(*s2=='\0')
			return (char*)cur;
		cur++;
	}
	return NULL;
}
int main()
{
	char* str1="hello world";
	char* str2="hello";
	char* ret=my_strstr(str1,str2);
	printf("%s\n",ret);
	return 0;
}
