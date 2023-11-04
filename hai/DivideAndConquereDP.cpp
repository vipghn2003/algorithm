#include<bits/stdc++.h>
#define ll long long
using namespace std;
 
const int N=3005;
 
int n,m,a[N],s[N],opt[N][N];
ll go_left[N][N], go_right[N][N], cost[N][N],dp[N][N];
 
template<typename T> inline void Cin(T &x)
{
    char c=getchar();
    x=0;
    while (c < '0' || c >'9')
        c = getchar();
    while (c>='0'&&c<='9')
        x=x*10+c-'0',c = getchar();
}
template <typename T, typename... Args> inline void Cin(T& a, Args&... args)
{
    Cin(a);
    Cin(args...);
}
 
 
void sol(int lev,int l,int r,int L,int R)
{
    if(l>r) return ;
    int mid=(l+r)/2;
    dp[mid][lev]=1e18;
    for(int i=L;i<=min(R,mid-1);i++)
    {
        long long cur=dp[i][lev-1]+cost[i][mid];
        if(dp[mid][lev]>cur)
        {
            opt[mid][lev]=i;
            dp[mid][lev]=cur;
        }
    }
    sol(lev,l,mid-1,L,min(opt[mid][lev],n));
    sol(lev,mid+1,r,max(1,opt[mid][lev]),R);
}
 
main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    Cin(n,m);
    for(int i=1;i<=n;i++)
    {
        Cin(a[i]);
        s[i] = s[i-1] + a[i];
        for(int k=0;k<=m;k++) dp[i][k]= 1e18;
    }
    for(int i=1;i<=n;i++)
    {
        go_left[i][i]=0;
        for(int mid=i+1;mid<=n;mid++) go_left[mid][i] = go_left[mid-1][i] + 1ll * (mid-i) * a[mid];
        go_right[i][i]=0;
        for(int mid=i-1;mid>=1;mid--) go_right[mid][i] = go_right[mid+1][i] + 1ll * (i-mid) * a[mid];
    }
    for(int i=1;i<=n;i++)
    {
        cost[i][i]=0;
        for(int j=i+1;j<=n;j++)
        {
            int mid = (i+j)/2;
            cost[i][j] = go_left[mid][i] + go_right[mid+1][j];
        }
    }
    for(int i=1;i<=n;i++) dp[i][1]=go_right[1][i];
    for(int lev=2;lev<=m;lev++) sol(lev,1,n,1,n);
    ll res=1e18;
    for(int i=1;i<=n;i++)
    {
        res=min(res, dp[i][m]+go_left[n][i]);
    }
    cout<<res;
}