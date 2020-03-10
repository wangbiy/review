#include "tcpServer.hpp"
void Usage(string proc)
{
	cout<<proc<<"PORT"<<endl;
}
int main(int argc,char* argv[])
{
	if(argc!=2)
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
