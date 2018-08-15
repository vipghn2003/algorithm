#include <bits/stdc++.h>
using namespace std;

namespace Lehmer {
    const int maxx = 1e2 + 5;
    const int maxy = 1e5 + 5;
    const int maxn = 1e7 + 5;
    const int maxp = 1e6 + 5;
    int np;
    int sp[maxn];
    int pr[maxp], cn[maxn];
    long long f[maxx][maxy];

    void init() {
        for (int i = 2; i < maxn; i += 2) sp[i] = 2;
        for (int i = 1; i < maxn; i += 2) sp[i] = i;
        for (int i = 3; i * i < maxn; i += 2) if (sp[i] == i) {
            for (int j = i * i; j < maxn; j += i + i) if (sp[j] == j) {
                sp[j] = i;
            }
        }
        np = 0;
        for (int i = 2; i < maxn; i++) {
            if (sp[i] == i) {
                pr[np++] = i;
            }
            cn[i] = np;
        }
        for (int i = 0; i < maxx; i++) {
            for (int j = 0; j < maxy; j++) {
                if (!i) f[i][j] = j;
                else f[i][j] = f[i - 1][j] - f[i - 1][j / pr[i - 1]];
            }
        }
    }
    long long LegendreSum(long long m, int n) {
        if (!n) return m;
        if (pr[n - 1] >= m) return 1;
        if (m < maxy && n < maxx) return f[n][m];
        return LegendreSum(m, n - 1) - LegendreSum(m / pr[n - 1], n - 1);
    }
    long long calc(long long m) {
        static int isinit;
        if (!isinit) {
            isinit = 1;
            init();
        }
        if (m < maxn) return cn[m];
        int x = sqrt(m + 0.9), y = cbrt(m + 0.9);
        int a = cn[y];
        long long res = LegendreSum(m, a) + a - 1;
        for (int i = a; pr[i] <= x; i++) res = res - calc(m / pr[i]) + calc(pr[i]) - 1;
        return res;
    }
}

int main() {
    assert(Lehmer::calc(1e10) == 455052511LL);
    cerr << "Correct\n";
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
