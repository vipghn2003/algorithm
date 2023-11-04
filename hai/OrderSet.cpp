#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
 
const int N=2e5+5;
tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>add_time[N],remove_time[N];
map<int,int>val;
 
/// order_of_key(x) returns number of elements strictly less than x
/// find_by_order(x) return (x-1)th largest element
 
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,cnt=0;
    cin>>n;
    while(n--)
    {
        int type,t,x;
        cin>>type>>t>>x;
        if(!val[x])
        {
            cnt++;
            val[x]=cnt;
        }
        int cur=val[x];
        if(type==1) add_time[cur].insert(t);
        if(type==2) remove_time[cur].insert(t);
        if(type==3) cout<<add_time[cur].order_of_key(t)-remove_time[cur].order_of_key(t)<<'\n';
    }
}