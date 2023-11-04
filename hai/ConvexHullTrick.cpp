#include<bits/stdc++.h>
#define int long long
#define ll long long
using namespace std;
 
struct Line {
  mutable ll m, b, p;
  bool operator<(const Line& o) const { return m < o.m; }
  bool operator<(ll x) const { return p < x; }
};
 
struct LineContainer : multiset<Line, less<>> {
  // (for doubles, use inf = 1/.0, div(a,b) = a/b)
  // max convexhull
  const ll inf = 1e18;
  ll div(ll a, ll b) { // floored division
    return a / b - ((a ^ b) < 0 && a % b);
  }
  bool isect(iterator x, iterator y) {
    if (y == end()) { x->p = inf; return false; }
    if (x->m == y->m) x->p = x->b > y->b ? inf : -inf;
    else x->p = div(y->b - x->b, x->m - y->m);
    return x->p >= y->p;
  }
  void add(ll m, ll b) {
    auto z = insert({m, b, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
  }
  ll query(ll x) {
    if(empty()) return -inf;
    auto l = *lower_bound(x);
    return l.m * x + l.b;
  }
}cht;
 
const int N=2e5+5;
int n, a[N], s[N];
 
 main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    int total=0;
    for(int i=1; i<=n; i++) {
        cin >> a[i];
        s[i] = s[i-1] + a[i];
        total += a[i]*i;
    }
    int res = total;
    for(int j=1; j<=n; j++) {
        // Lay thang a[i] vao vi tri j : i < j: total - (s[j] - s[i]) - a[i]*i + a[i]*j = total - s[j] + (s[i]- a[i]*i) +a[i]*j;
        int val = cht.query(j);
        res = max(res, total - s[j] + val);
        cht.add(a[j], s[j] - a[j]*j);
    }
    cht.clear();
    for(int j=n; j>=0; j--) {
        // Lay thang a[i] vao vi tri j : i > j: total + (s[i-1] - s[j]) - a[i]*i + a[i]*(j+1) = total - s[j] + (s[i-1] - a[i]*i) +a[i]*(j+1);
        int val = cht.query(j+1);
        res = max(res, total - s[j] +val);
        cht.add(a[j], s[j-1] - a[j]*j);
    }
    cout << res;
 
}