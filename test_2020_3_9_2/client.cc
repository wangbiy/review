#include "udpClient.hpp"
void Usage(string proc)
{
	cout<<proc<<"IP"<<" "<<"PORT"<<endl;
}
int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		Usage(argv[0]);
		exit(1);
	}
	Client* cp=new Client(argv[1],atoi(argv[2]));
	cp->InitClient();
	cp->Run();
	delete cp;
	return 0;
}
