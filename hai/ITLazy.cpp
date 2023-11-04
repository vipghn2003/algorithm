#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+1;
 
int n,i,j,a[N],ST[4*N],lazy[4*N];
 
void build (int id,int l,int r)
{
    if (l==r)
    {
        ST[id]=a[l];
        return;
    }
    int mid=(l+r)/2;
    build(id*2,l,mid);
    build (id*2+1,mid+1,r);
    ST[id]=max (ST[id*2],ST[id*2+1]);
 
}
 
void dolazy(int id,int l,int r)
{
    if (lazy[id]==0) return;
    ST[id]+=lazy[id];
    if (l!=r)
    {
        lazy[id*2]+=lazy[id];
        lazy[id*2+1]+=lazy[id];
    }
    lazy[id]=0;
}
 
void update(int id,int l,int r,int L,int R,int val)
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
    update(id*2,l,mid,L,R,val);
    update(id*2+1,mid+1,r,L,R,val);
    ST[id]=max(ST[id*2],ST[id*2+1]);
}
 
int get (int id,int l,int r,int L,int R)
{
    dolazy(id,l,r);
    if (r<L||R<l) return (int)-1e18;
    if (L<=l&&r<=R) return ST[id];
    int mid=(l+r)/2;
    return max (get (id*2,l,mid,L,R),get (id*2+1,mid+1,r,L,R));
}
 
main()
{
    cin>>n;
    for(i=1; i<=n; i++)
        cin>>a[i];
    build(1,1,n);
    int q;
    cin>>q;
    while(q--)
    {
        int p;
        cin>>p;
        if(p==1)
        {
            int x,y,val;
            cin>>x>>y>>val;
            update(1,1,n,x,y,val);
        }
        else
        {
            int x,y;
            cin>>x>>y;
            cout<<get(1,1,n,x,y)<<'\n';
        }
    }
}