#include<bits/stdc++.h>
#define fi first
#define se second
#define pii pair<int,int>
#define mp make_pair
using namespace std;
 
const int N=1e5+5;
int n,l[N],r[N],level[N],p[N][20],total_num,node[N*2];
vector<int>adj[N];
 
int cnt=0;
void dfs(int x,int pa=-1)
{
    for(int i=1;i<=18;i++) p[x][i]=p[p[x][i-1]][i-1];
    cnt++;
    l[x]=cnt;
    for(auto&u:adj[x])
    {
        if(u==pa) continue;
        level[u]=level[x]+1;
        p[u][0]=x;
        dfs(u,x);
    }
    r[x]=cnt;
}
 
int lca(int x,int y)
{
    if(level[x]>level[y]) swap(x,y);
    int diff=level[y]-level[x];
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
 
bool isParent(int p,int u)
{
    return (l[p]<=l[u]&&l[u]<=r[p]);
}
 
bool lf(const int &x,const int &y)
{
    return l[x]<l[y];
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
    dfs(1);
    for(int i=1;i<=n;i++)
    {
        int edge=0;
        total_num=1;
        node[1]=1;
        for(int j=i;j<=n;j+=i)
        {
            total_num++;
            node[total_num]=j;
        }
        sort(node+1,node+total_num+1,lf);
        total_num=unique(node+1,node+total_num+1)-node-1;
        int now=total_num;
        for(int j=1;j<now;j++)
        {
            total_num++;
            node[total_num]=lca(node[j],node[j+1]);
        }
        sort(node+1,node+total_num+1,lf);
        total_num=unique(node+1,node+total_num+1)-node-1;
        stack<int>st;
        st.push(node[1]);
        for(int j=2;j<=total_num;j++)
        {
            while(!st.empty()&&!isParent(st.top(),node[j])) st.pop();
            if(!st.empty())
            {
                int par=st.top();
                edge+=level[node[j]]-level[par];
            }
            st.push(node[j]);
        }
        cout<<edge*2<<'\n';
    }
}