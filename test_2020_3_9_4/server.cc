#include "tcpServer.hpp"
void Usage(string proc)
{
	cout<<proc<<"IP"<<" "<<"PORT"<<endl;
}
int main(int argc,char* argv[])
{
	if(argc!=2)//由于不需要ip地址，因此命令行参数改为2个
	{
		Usage(argv[0]);
		exit(1);
	}
	int port=atoi(argv[1]);
	Server* sp=new Server(port);
	sp->InitServer();
	sp->Start();
	delete sp;
	return 0;
}
