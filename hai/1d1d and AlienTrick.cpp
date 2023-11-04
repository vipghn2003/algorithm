#include<bits/stdc++.h>
#define pii pair<long long,int>
#define fi first
#define se second
#define mp make_pair
using namespace std;
 
const int N=3e5+5;
int n,k,a[N],cut[N];
long long s[N],dp[N];
 
long long cost(int l,int r)
{
    int mid=(l+r+1)/2;
    return (s[r]-s[mid])-1ll*a[mid]*(r-mid)+1ll*a[mid]*(mid-l)-(s[mid]-s[l]);
}
 
struct T
{
    int j,l,r;
};
 
bool better(int i,int j,int x)
{
    return mp(dp[i]+cost(i,x),cut[i])<mp(dp[j]+cost(j,x),cut[j]);
}
 
pii calc(long long C)
{
    dp[0]=cut[0]=0;
    deque<T>now;
    now.push_back({0,1,n}); /// j,l,r: j is best for dp[l,r]
    for(int i=1;i<=n;i++)
    {
        if(now[0].r<i) now.pop_front();
        dp[i]=dp[now[0].j]+cost(now[0].j,i)+C;
        cut[i]=cut[now[0].j]+1;
        now[0].l=i+1;
        while(now.size()&&better(i,now.back().j,now.back().l)) now.pop_back();
        if(now.size())
        {
            int l=now.back().l,r=now.back().r,id;
            while(l<=r)
            {
                int m=(l+r)/2;
                if(better(i,now.back().j,m)) r=m-1;
                else
                {
                    id=m;
                    l=m+1;
                }
            }
            now.back().r=id;
            if(l>n) continue;
            now.push_back({i,l,n});
        }
        else  now.push_back({i,i+1,n});
    }
    return mp(dp[n],cut[n]);
}
 
main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        s[i]=s[i-1]+a[i];
    }
    long long l=0,r=cost(0,n)+100,res;
    while(l<=r)
    {
        long long mid=(l+r)/2;
        if(calc(mid).se>k) l=mid+1;
        else
        {
            res=mid;
            r=mid-1;
        }
    }
    cout<<calc(res).fi-res*k;
}