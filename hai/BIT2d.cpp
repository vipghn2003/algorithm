#include <bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
using namespace std;
const int N=1e5+5;
struct BIT2D
{
    const int inf = 2e9;
    int n;
    vector<vector<int>>nodes,f;
    void fakeUpdate(int u, int v)
    {
        for (int x = u; x <=n; x += x & -x) nodes[x].push_back(v);
    }
    void fakeGet(int u, int v)
    {
        for (int x = u; x > 0; x -= x & -x) nodes[x].push_back(v);
    }
    void update(int u, int v,int val)
    {
        for (int x = u; x <=n; x += x & -x)
        {
            for (int y = lower_bound(nodes[x].begin(), nodes[x].end(), v) - nodes[x].begin()+1; y <=nodes[x].size() ; y += y & -y)
                f[x][y]+=val;
        }
    }
    int get(int u, int v)
    {
        int res=0;
        for (int x = u; x > 0 ; x -= x & -x)
        {
            for (int y = upper_bound(nodes[x].begin(), nodes[x].end(), v) - nodes[x].begin() ; y > 0; y -= y & -y)
                res += f[x][y];
        }
        return res;
    }
    void init(int _n)
    {
        n = _n;
        nodes.assign(n + 5, {});
        f.assign(n + 5, {});
    }
    void normalize()
    {
        for(int i=1;i<=n;i++)
        {
            nodes[i].push_back(inf);
            sort(nodes[i].begin(), nodes[i].end());
            f[i].resize(nodes[i].size()+3);
        }
    }
} ft;
int n,q,ans[N],x[N],y[N],w[N];
pair<int,int>stu[N];
vector<int>val;
int compress(int x)
{
    return lower_bound(val.begin(),val.end(),x)-val.begin()+1;
}
struct Q
{
    int type,x,y,w;
    int l,r,u,d;
};
Q query[N];
main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>q;
    for(int i=1;i<=n;i++)
    {
        cin>>x[i]>>y[i]>>w[i];
        val.push_back(x[i]);
        val.push_back(y[i]);
    }
    for(int i=1;i<=q;i++)
    {
        cin>>query[i].type;
        if(query[i].type==0)
        {
            cin>>query[i].x>>query[i].y>>query[i].w;
            val.push_back(query[i].x);
            val.push_back(query[i].y);
        }
        else
        {
            cin>>query[i].l>>query[i].d>>query[i].r>>query[i].u;
            val.push_back(query[i].l-1);
            val.push_back(query[i].d-1);
            val.push_back(query[i].r-1);
            val.push_back(query[i].u-1);
        }
    }
    sort(val.begin(),val.end());
    val.erase(unique(val.begin(),val.end()),val.end());
    ft.init(val.size());
    for(int i=1;i<=n;i++) ft.fakeUpdate(compress(x[i]),compress(y[i]));
    for(int i=1;i<=q;i++) if(query[i].type==0) ft.fakeUpdate(compress(query[i].x),compress(query[i].y));
    for(int i=1;i<=q;i++)
    {
        if(query[i].type==1)
        {
            ft.fakeGet(compress(query[i].r-1),compress(query[i].u-1));
            ft.fakeGet(compress(query[i].l-1),compress(query[i].d-1));
            ft.fakeGet(compress(query[i].r-1),compress(query[i].d-1));
            ft.fakeGet(compress(query[i].l-1),compress(query[i].u-1));
        }
    }
    ft.normalize();
    for(int i=1;i<=n;i++)
    {
        ft.update(compress(x[i]),compress(y[i]),w[i]);
    }
    for(int i=1;i<=q;i++)
    {
        if(query[i].type==1)
        {
            int res=0;
            res+=ft.get(compress(query[i].r-1),compress(query[i].u-1));
            res+=ft.get(compress(query[i].l-1),compress(query[i].d-1));
            res-=ft.get(compress(query[i].r-1),compress(query[i].d-1));
            res-=ft.get(compress(query[i].l-1),compress(query[i].u-1));
            cout<<res<<'\n';
        }
        else ft.update(compress(query[i].x),compress(query[i].y),query[i].w);
    }
}
