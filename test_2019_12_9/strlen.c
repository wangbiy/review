#include <stdio.h>
#include <assert.h>
//1、模拟实现strlen函数
int my_strlen1(const char* str)
{
	assert(str);
	if(*str=='\0')
		return 0;
	else
		return 1+my_strlen1(str+1);
}
int my_strlen2(const char* str)
{
	assert(str);
	int count=0;
	while(*str!='\0')
	{
		count++;
		str++;
	}
	return count;
}
int my_strlen3(const char* str)
{
	assert(str);
	const char* start=str;
	while(*str!='\0')
	{
		str++;
	}
	return str-start;
}
int main()
{
	const char *str="abvhgkl";
	int len1=my_strlen1(str);
	int len2=my_strlen2(str);
	int len3=my_strlen3(str);
	printf("%d\n",len1);
	printf("%d\n",len2);
	printf("%d\n",len3);
	return 0;
}
