#include<bits/stdc++.h>
using namespace std;
 
const int N=2e5+5;
const int S=sqrt(N);
int n,q,a[N],res[N],occ[N],cnt[S][S],sum[S];
int dep[N],p[N][20],out[N],in[N],id[N];
vector<pair<int,int>>adj[N];
 
struct Query
{
    int l,r,id,p;
};
Query Q[N];
 
bool lf( Query A, Query B)
{
  if (A.l/S!=B.l/S) return A.l/S<B.l/S;
  return A.r<B.r;
}
 
int cur;
void dfs(int u)
{
    in[u]=++cur;
    id[cur]=u;
    for(int k=1;k<=18;k++) p[u][k]=p[p[u][k-1]][k-1];
    for(auto&v:adj[u])
    {
        if(v.first==p[u][0]) continue;
        p[v.first][0]=u;
        a[v.first]=v.second;
        dep[v.first]=dep[u]+1;
        dfs(v.first);
    }
    out[u]=++cur;
    id[cur]=u;
}
 
int lca(int x,int y)
{
    if(dep[x]>dep[y]) swap(x,y);
    int diff=dep[y]-dep[x];
    for(int k=18;k>=0;k--) if(diff>>k&1) y=p[y][k];
    if (x==y) return x;
    for(int k=18;k>=0;k--)
    {
        if (p[x][k]!=p[y][k])
        {
            x=p[x][k];
            y=p[y][k];
        }
    }
    return p[x][0];
}
 
void add(int v)
{
    if(v>n) return ;
    cnt[v/S][v%S]++;
    if(cnt[v/S][v%S]==1) sum[v/S]++;
}
 
void del(int v)
{
    if(v>n) return;
    cnt[v/S][v%S]--;
    if(cnt[v/S][v%S]==0) sum[v/S]--;
}
 
void Insert(int p)
{
	int o=id[p];
	occ[o]++;
	if(occ[o]==2) del(a[o]);
	else if(occ[o]==1) add(a[o]);
}
 
void Erase(int p)
{
	int o=id[p];
	occ[o]--;
	if(occ[o]==1) add(a[o]);
	else if(occ[o]==0) del(a[o]);
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>q;
    for(int i=1;i<=n;i++)
    {
        adj[i].clear();
        for(int k=0;k<=18;k++) p[i][k]=0;
        occ[i]=0;
    }
    for(int i=1;i<n;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    cur=0;
    a[1]=N;
    dfs(1);
    for(int i=1;i<=q;i++)
    {
        Q[i].id=i;
        int u,v;
        cin>>u>>v;
        if(in[u]>in[v]) swap(u,v);
        int g=lca(u,v);
        if(g==u)
        {
            Q[i].l=in[u]+1;
            Q[i].r=in[v];
        }
        else
        {
            Q[i].l=out[u];
            Q[i].r=in[v];
        }
    }
    sort(Q+1,Q+q+1,lf);
    int L=1;
    int R=1;
    Insert(1);
    for(int i=1;i<=q;i++)
    {
        int ql=Q[i].l;
        int qr=Q[i].r;
        while(R<qr) Insert(++R);
	    while(L>ql) Insert(--L);
	    while(L<ql) Erase(L++);
	    while(R>qr) Erase(R--);
	    for(int j=0;j<S;j++)
        {
            if(sum[j]!=S)
            {
                for(int k=0;k<S;k++)
                {
                    if(!cnt[j][k])
                    {
                        res[Q[i].id]=j*S+k;
                        break;
                    }
                }
                break;
            }
        }
    }
    for(int i=1;i<=q;i++) cout<<res[i]<<'\n';
}
 