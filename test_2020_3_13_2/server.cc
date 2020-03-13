#include "epollServer.hpp"
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
	Server* sp=new Server(atoi(argv[1]));
	sp->InitServer();
	sp->Run();
	delete sp;
	return 0;
}
