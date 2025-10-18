#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 200000 + 5;
int N, Q;
int A[MAXN];
vector<int> g[MAXN];

int parent_[MAXN], depth_[MAXN], heavy_[MAXN];
int sz_[MAXN];
int head_[MAXN], pos_[MAXN];
int cur_pos = 1; // 1-indexed positions

// Fenwick Tree
struct BIT {
    int n;
    vector<int> bit;
    BIT() {}
    BIT(int n) : n(n), bit(n + 1, 0) {}
    void init(int n_) {
        n = n_;
        bit.assign(n + 1, 0);
    }
    void add(int i, int v) {
        for (; i <= n; i += i & -i) {
            bit[i] += v;
        }
    }
    int sumPrefix(int i) {
        int s = 0;
        for (; i > 0; i -= i & -i) {
            s += bit[i];
        }
        return s;
    }
    int rangeSum(int l, int r) {
        if (l > r) {
            return 0;
        }
        return sumPrefix(r) - sumPrefix(l - 1);
    }
};
BIT bit;

int dfs_sz(int u, int p){
    parent_[u] = p;
    depth_[u] = (p == -1 ? 0 : depth_[p] + 1);
    sz_[u] = 1;
    heavy_[u] = -1;

    int max_sz = 0;

    for (int v : g[u]) {
        if (v != p) {
            int sub = dfs_sz(v, u);
            sz_[u] += sub;
            if (sub > max_sz) {
                max_sz = sub;
                heavy_[u] = v;
            }
        }
    }
    return sz_[u];
}

void dfs_hld(int u, int h){
    head_[u] = h;
    pos_[u] = cur_pos++;
    if(heavy_[u] != -1){
        dfs_hld(heavy_[u], h);
    }
    for (int v : g[u]) {
        if (v != parent_[u] && v != heavy_[u]) {
            dfs_hld(v, v);
        }
    }
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    if(!(cin >> N >> Q)) return 0;
    for(int i=1;i<=N;i++) cin >> A[i];
    for(int i=0;i<N-1;i++){
        int a,b; cin >> a >> b;
        g[a].push_back(b); g[b].push_back(a);
    }

    dfs_sz(1, -1);
    dfs_hld(1, 1);
    for (int i = 1; i <= N; i++) {
        cout << setw(3) << i << " \n"[i == N];
    }
    for (int i = 1; i <= N; i++) {
        cout << setw(3) << head_[i] << " \n"[i == N];
    }
    for (int i = 1; i <= N; i++) {
        cout << setw(3) << pos_[i] << " \n"[i == N];
    }
    cout << endl;

    bit.init(N);
    // Build BIT with base array where base[pos[u]] = A[u]
    for (int u = 1; u <= N; ++u) {
        bit.add(pos_[u], A[u]);
    }

    while(Q--){
        int type; cin >> type;
        if(type==1){
            int u; int x; cin >> u >> x;
            // set value[u] = x => update by delta at pos[u]
            int delta = x - A[u];
            A[u] = x;
            bit.add(pos_[u], delta);
        }else{
            int u; cin >> u;
            int l = pos_[u];
            int r = pos_[u] + sz_[u] - 1;
            cout << bit.rangeSum(l, r) << '\n';
        }
    }
    return 0;
}
