#include <iostream>
using namespace std;
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#define PATH_NAME "/tmp"//路径
#define PROJ_ID 0x6666
#define SIZE 4096
//共享内存
int main()
{
	//创建/打开共享内存
	key_t key=ftok(PATH_NAME,PROJ_ID);//得到key
	if(key<0)
	{
		cout<<"ftok error"<<endl;
		return 1;
	}
	int shm_id=shmget(key,SIZE,IPC_CREAT|IPC_EXCL|0644);
	if(shm_id<0)
	{
		cout<<"shmget error"<<endl;
		return 2;
	}
	//此时如果运行就会发现只有第一次运行成功，后面运行就会报错，因为共享内存生命周期随内核，我们只有使用ipcrm -m +指定shmid这个命令才能删除创建的这个共享内存，之后再次运行才可以，因此有了shmctl函数来控制共享内存
	//要实现共享内存进行进程间通信
	//首先先让共享内存映射到进程地址空间
	char* p=(char*)shmat(shm_id,nullptr,0);//挂接
	//使用共享内存
	int i=0;
	while(i<SIZE)
	{
		cout<<p<<endl;
		sleep(1);
		i++;
	}
	shmdt(p);//脱离挂接
	//控制共享内存
	shmctl(shm_id,IPC_RMID,nullptr);//表示删除共享内存
	return 0;
}
