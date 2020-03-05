#include <iostream>
using namespace std;
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
//系统文件IO
//open系统调用函数
//int main()
//{
//	umask(0);
//	int fd=open("log.txt",O_WRONLY|O_CREAT,0644);
//	if(fd<0)
//	{
//		cout<<"open error"<<endl;
//		return 0;
//	}
//	//进行写操作
//	const char* msg="hello world\n";
//	write(fd,msg,strlen(msg));
//	close(fd);
//}
//fd是什么
//int main()
//{
//	int fd0=open("log0.txt",O_WRONLY|O_CREAT,0644);
//	int fd1=open("log1.txt",O_WRONLY|O_CREAT,0644);
//	int fd2=open("log2.txt",O_WRONLY|O_CREAT,0644);
//	int fd3=open("log3.txt",O_WRONLY|O_CREAT,0644);
//	int fd4=open("log4.txt",O_WRONLY|O_CREAT,0644);
//	int fd5=open("log5.txt",O_WRONLY|O_CREAT,0644);
//	cout<<"fd0:"<<fd0<<endl;
//	cout<<"fd1:"<<fd1<<endl;
//	cout<<"fd2:"<<fd2<<endl;
//	cout<<"fd3:"<<fd3<<endl;
//	cout<<"fd4:"<<fd4<<endl;
//	cout<<"fd5:"<<fd5<<endl;
//	close(fd0);
//	close(fd1);
//	close(fd2);
//	close(fd3);
//	close(fd4);
//	close(fd5);
//
//	return 0;
//}
//read系统调用函数
//int main()
//{
//	int fd=open("log0.txt",O_RDONLY);
//	if(fd<0)
//		cout<<"open error"<<endl;
//	//char c;
//	//while(read(fd,&c,1)>0)
//	//	putchar(c);
//	char c[1024];
//	ssize_t s=read(fd,c,1024);
//	if(s>0)
//	{
//		c[s]=0;
//		cout<<s<<endl;
//		cout<<c<<endl;
//	}
//	close(fd);
//	return 0;
//}
//文件描述符的分配规则
//int main()
//{
//	close(0);//将标准输入关闭
//	int fd0=open("log0.txt",O_WRONLY|O_CREAT,0644);
//	int fd1=open("log1.txt",O_WRONLY|O_CREAT,0644);
//	int fd2=open("log2.txt",O_WRONLY|O_CREAT,0644);
//	int fd3=open("log3.txt",O_WRONLY|O_CREAT,0644);
//	int fd4=open("log4.txt",O_WRONLY|O_CREAT,0644);
//	int fd5=open("log5.txt",O_WRONLY|O_CREAT,0644);
//
//
//	cout<<"fd0: "<<fd0<<endl;
//	cout<<"fd1: "<<fd1<<endl;
//	cout<<"fd2: "<<fd2<<endl;
//	cout<<"fd3: "<<fd3<<endl;
//	cout<<"fd4: "<<fd4<<endl;
//	cout<<"fd5: "<<fd5<<endl;
//	return 0;
//}
//输出重定向
//int main()
//{
//	close(1);//关掉指向标准输出文件描述符
//	int fd0=open("log0.txt",O_WRONLY|O_CREAT,0644);//此时fd0占用的就是1
//	int fd1=open("log1.txt",O_WRONLY|O_CREAT,0644);
//	int fd2=open("log2.txt",O_WRONLY|O_CREAT,0644);
//	int fd3=open("log3.txt",O_WRONLY|O_CREAT,0644);
//	int fd4=open("log4.txt",O_WRONLY|O_CREAT,0644);
//	int fd5=open("log5.txt",O_WRONLY|O_CREAT,0644);
//	cout<<"fd0: "<<fd0<<endl;
//	cout<<"fd1: "<<fd1<<endl;
//	cout<<"fd2: "<<fd2<<endl;
//	cout<<"fd3: "<<fd3<<endl;
//	cout<<"fd4: "<<fd4<<endl;
//	cout<<"fd5: "<<fd5<<endl;
//
//	//此时应该输出到显示器的内容却在log0.txt中，因为此时先关闭了标准输出，然后fd0占用了
//	return 0;
//}
//重定向原理
//将标准输出关掉，将原本输出的内容重定向到指定文件中
//int main()
//{
//	close(1);
//	FILE* pf=fopen("log0.txt","a");
//	const char* msg="helo world\n";
//	cout<<"hello world"<<endl;
//	fflush(stdout);//刷新标准输出
//	fclose(pf);
//	return 0;
//}
//dup2系统调用
int main()
{
	int fd=open("log0.txt",O_WRONLY|O_CREAT,0644);
	if(fd<0)
		cout<<"open error"<<endl;
	dup2(fd,1);//将标准输出重定向到log0.txt中
	cout<<"hello world"<<endl;
	fflush(stdout);//必须刷新，因为数据在C语言的缓冲区中，不刷新数据还是在缓冲区中，没有放在文件中
	return 0;
}
