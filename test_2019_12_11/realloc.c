#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
void* my_realloc(void* memblock,size_t size)
{
	void* new_base=malloc(size);//申请新空间
	if(new_base==NULL)
	{
		return NULL;
	}
	memcpy(new_base,memblock,size);//拷贝原内容
	free(memblock);
	memblock=new_base;
	return memblock;
}
struct S
{
	int n;
	char arr[];//柔性数组

};
int main()
{
	struct S *p=(struct S*)malloc(sizeof(struct S) + 10 * (sizeof(char)));
	int i = 0;
	struct S *ptr;
	p->n = 10;
	for (i = 0; i < 10; ++i)
	{
		p->arr[i] = i + 1;
		printf("%d ", p->arr[i]);
	}
	printf("\n");
	ptr = my_realloc(p,sizeof(struct S)+20 * (sizeof(char)));
	if (ptr != NULL)
	{
		p = ptr;
	}
	p->n = 20;
	for (i = 0; i < 20; ++i)
	{
		p->arr[i] = i + 1;
		printf("%d ", p->arr[i]);
	}
	printf("\n");
	free(p);
	p = NULL;
	return 0;
}
