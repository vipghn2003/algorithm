int u[N], divv[N];
void init() {
    memset(divv, -1, sizeof divv);
    memset(u, -1, sizeof u);
    for(int i=2; i <= N-5; i++) {
        if(divv[i] != -1) continue;
        for(int j=i*2; j <= N-5; j+=i) divv[j] = i;
    }
    for(int i=1; i <= N-5; i++) {
        int tmp = i;
        vector<int>p;
        while(divv[tmp] != -1) {
                p.push_back(divv[tmp]);
                tmp/=divv[tmp];
        }
        if(tmp != 1) p.push_back(tmp);
        if(p.empty()) {
            u[i] = 1;
            continue;
        }
        sort(p.begin(), p.end());
        for(int j=0; j<p.size()-1; j++) if(p[j] == p[j+1]) u[i] = 0;
        if(u[i] == 0) continue;
        if(p.size()%2==0) u[i] = 1;
    }
}