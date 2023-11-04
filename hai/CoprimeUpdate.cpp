#include<bits/stdc++.h>
#define int long long
 
using namespace std;
 
const int N=1e5+5;
 
int n,a[N],cnt[N];
bool kt[N];
vector<int>divs[N],p[N];
 
void init()
{
    for(int i=1;i<=N-5;i++)
    {
        for(int j=1;j*j<=i;j++)
        {
            if(i%j==0)
            {
                divs[i].push_back(j);
                if(i!=j*j) divs[i].push_back(i/j);
            }
        }
    }
    for(int t=1;t<=N-5;t++)
    {
        int i=t;
        for(int j=2;j*j<=i;j++)
        {
            if(i%j==0)
            {
                p[t].push_back(j);
                while(i%j==0) i/=j;
            }
        }
        if(i!=1) p[t].push_back(i);
    }
}
 
void updateCnts(int x, int val)
{
    for(auto&num:divs[x]) cnt[num]+=val;
}
 
int getCoprime(int x)
{
    int pNum=p[x].size();
    int result=0;
    for(int mask=1;mask<(1<<pNum);mask++)
    {
        int prod=1;
        for(int i=0;i<pNum;i++)
        {
            if(mask>>i&1) prod*=p[x][i];
        }
        if (__builtin_popcount(mask)&1) result+=cnt[prod];
        else result-=cnt[prod];
    }
    return result;
}
 
main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        kt[a[i]]=true;
    }
    vector<int>now;
    int res=*max_element(a+1,a+n+1);
    stack<int>st;
    for(int i=1;i<=N-5;i++)
    {
        now.clear();
        for(int j=i;j<=N-5;j+=i) if(kt[j]) now.push_back(j/i);
        reverse(now.begin(),now.end());
        for(auto&x:now)
        {
            int coprime=st.size()-getCoprime(x);
            while(coprime)
            {
                if(__gcd(x,st.top())==1)
                {
                    res=max(res,x*st.top()*i);
                    coprime--;
                }
                updateCnts(st.top(),-1);
                st.pop();
            }
            updateCnts(x,1);
            st.push(x);
        }
        while (!st.empty())
        {
            updateCnts(st.top(),-1);
            st.pop();
        }
    }
    cout<<res;
}