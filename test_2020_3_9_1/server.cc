#include "udpServer.hpp"
void Usage(string proc)
{
	cout<<proc<<"IP"<<" "<<"PORT"<<endl;
}
int main(int argc,char* argv[])//命令行参数必须是3个，即./server ip port三部分
{
	if(argc!=3)//无法运行
	{
		Usage(argv[0]);
		exit(1);
	}
	Server* sp=new Server(argv[1],atoi(argv[2]));
	sp->InitServer();
	sp->Start();
	delete sp;
	return 0;
}

