#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	char str[]="xxx@qq.com";
	char buf[30]={0};
	char* ret=NULL;
	char* sep="@.";
	strcpy(buf,str);
	for(ret=strtok(buf,sep);ret!=NULL;ret=strtok(NULL,sep))
	{
		printf("%s\n",ret);
	}
	return 0;
}
