#include<bits/stdc++.h>
using namespace std;
 
const int N=1e5+5;
int n,p[N],sz[N],m,pos[N],b[N],chain,Inchain[N],Stchain[N],r[N];
int ST[4*N],lazy[4*N];
vector<int>adj[N];
 
void FindSize(int x)
{
    sz[x]=1;
    for(auto&u:adj[x])
    {
        if(u!=p[x])
        {
            p[u]=x;
            FindSize(u);
            sz[x]+=sz[u];
        }
    }
}
 
void hld(int x)
{
    if(Stchain[chain]==0) Stchain[chain]=x;
    m++;
    b[m]=x;
    pos[x]=m;
    Inchain[x]=chain;
    int bigchild=0;
    for(auto&u:adj[x])
    {
        if(u!=p[x]&&sz[u]>sz[bigchild]) bigchild=u;
    }
    if(bigchild!=0) hld(bigchild);
    for(auto&u:adj[x])
    {
        if(u!=p[x]&&u!=bigchild)
        {
            chain++;
            hld(u);
        }
    }
    r[x]=m;
}
 
void dolazy(int id,int l,int r)
{
    if (lazy[id]==0)
        return;
    ST[id]+=lazy[id];
    if (l!=r)
    {
        lazy[id*2]+=lazy[id];
        lazy[id*2+1]+=lazy[id];
    }
    lazy[id]=0;
}
 
void Update(int id,int l,int r,int L,int R,int val)
{
    dolazy(id,l,r);
    if (r<L||R<l) return;
    if(L<=l&&r<=R)
    {
        ST[id]+=val;
        if (l!=r)
        {
            lazy[id*2]+=val;
            lazy[id*2+1]+=val;
        }
        return;
    }
    int mid=(l+r)/2;
    Update(id*2,l,mid,L,R,val);
    Update(id*2+1,mid+1,r,L,R,val);
    ST[id]=max(ST[id*2],ST[id*2+1]);
}
 
int get (int id,int l,int r,int L,int R)
{
    dolazy(id,l,r);
    if (r<L||R<l)return 0;
    if (L<=l&&r<=R) return ST[id];
    int mid=(l+r)/2;
    return max (get (id*2,l,mid,L,R),get (id*2+1,mid+1,r,L,R));
}
 
void Upd_path(int u,int a,int val)
{
    while(true)
    {
        if(Inchain[u]==Inchain[a])
        {
            Update(1,1,n,pos[a],pos[u],val);
            break;
        }
        int uchain=Inchain[u];
        Update(1,1,n,pos[Stchain[uchain]],pos[u],val);
        u=p[Stchain[uchain]];
    }
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for(int i=1;i<n;i++)
    {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    chain=1;
    FindSize(1);
    hld(1);
    int sum=0;
    for(int i=1;i<=n;i++)
    {
        int x;
        cin>>x;
        Upd_path(i,1,x);
        sum+=x;
    }
    int q;
    cin>>q;
    while(q--)
    {
        char type;
        cin>>type;
        if(type=='Q')
        {
            int x;
            cin>>x;
            cout<<max(get(1,1,n,pos[x]+1,r[x]),sum-get(1,1,n,pos[x],pos[x]))<<'\n';
        }
        else
        {
            int x,y;
            cin>>x>>y;
            Upd_path(x,1,y);
        }
    }
}