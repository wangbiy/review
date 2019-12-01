#include <iostream>
using namespace std;
int main()
{
    for(int i=0;i<=9;++i)
    {
        int sum=1;
        for(int j=0;j<=9;++j)
        {
            cout<<i<<"*"<<j<<"= "<<i*j<<" ";
        }
        cout<<endl;
    }
    return 0;
}
