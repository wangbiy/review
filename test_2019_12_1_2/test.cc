#include <iostream>
using namespace std;
#include <algorithm>
bool IsPrime(int a)
{
    for(int i=2;i<sqrt(a);++i)
    {
        if(a%i==0)
            return false;
    }
    return true;
}
int main()
{
    for(int i=100;i<=200;++i)
    {
        if(IsPrime(i))
            cout<<i<<" ";
    }
    cout<<endl;
    return 0;
}

