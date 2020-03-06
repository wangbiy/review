#include <iostream>
using namespace std;
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/shm.h>
#define PATH_NAME "/tmp"
#define PROJ_ID 0x6666
#define SIZE 4096
//共享内存客户端
int main()
{
	key_t key=ftok(PATH_NAME,PROJ_ID);
	if(key<0)
	{
		cout<<"ftok error"<<endl;
		return 1;
	}
	int shm_id=shmget(key,SIZE,0);//打开服务端创建好的共享内存
	if(shm_id<0)
	{
		cout<<"shmget error"<<endl;
		return 2;
	}
	sleep(3);
	char* p=(char*)shmat(shm_id,nullptr,0);
	//向共享内存写入内容
	int i=0;
	while(i<SIZE)
	{
		p[i]='a'+i;
		i++;
		p[i]=0;
		sleep(1);
	}
	shmdt(p);//脱离挂接
	//不需要删除共享内存，因为没有创建
	return 0;
}
