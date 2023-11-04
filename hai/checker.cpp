#include<bits/stdc++.h>
 
using namespace std;
int rnd(int l,int r)
{
    return l+rand()%(r-l+1);
}
 
bool vis[30];
main()
{
    srand(time(NULL));
    for(;;)
    {
        ofstream cout("A.inp");
        int n=10;
        int m=10;
        cout<<n<<' '<<m<<'\n';
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++) cout<<rnd(100000,1000000)<<' ';
            cout<<'\n';
        }
        cout.close();
        system("A.exe");
        system("A1.exe");
        if(system("fc A.OUT A1.OUT")) return cout<<"WA",0;
        else cout<<"AC";
    }
}