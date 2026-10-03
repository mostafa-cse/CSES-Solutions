#include <bits/stdc++.h>
using namespace std;

struct FCBLCA {
    int n;
    vector<vector<int>> adj;
    vector<int> depth;

    vector<int> euler;
    vector<int> eulerDepth;
    vector<int> first;

    int B = 1;
    int m = 0;
    int nb = 0;
    vector<int> blockId;
    vector<int> blockMinIdx;
    vector<vector<vector<int>>> inBlock;

    vector<vector<int>> st;
    vector<int> lg;

    explicit FCBLCA(int n = 0) { init(n); }

    void init(int n_) {
        n = n_;
        adj.assign(n, {});
        depth.assign(n, 0);
        first.assign(n, -1);
        euler.clear();
        eulerDepth.clear();
        blockId.clear();
        blockMinIdx.clear();
        inBlock.clear();
        st.clear();
        lg.clear();
        B = 1; m = 0; nb = 0;
    }

    inline void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u, int p, int d) {
        depth[u] = d;
        first[u] = (int)euler.size();
        euler.push_back(u);
        eulerDepth.push_back(d);
        for (int v : adj[u]) if (v != p) {
            dfs(v, u, d + 1);
            euler.push_back(u);
            eulerDepth.push_back(d);
        }
    }

    inline int betterIdx(int i, int j) const {
        if (i < 0) return j;
        if (j < 0) return i;
        if (eulerDepth[i] != eulerDepth[j]) return (eulerDepth[i] < eulerDepth[j]) ? i : j;
        return (i < j) ? i : j;
    }

    void buildInBlockTables() {
        const int types = 1 << (B - 1);
        inBlock.assign(types, vector<vector<int>>(B, vector<int>(B, 0)));
        vector<int> delta(B);
        for (int t = 0; t < types; ++t) {
            delta[0] = 0;
            for (int i = 0; i < B - 1; ++i) {
                delta[i + 1] = delta[i] + ((t >> i) & 1 ? +1 : -1);
            }
            for (int l = 0; l < B; ++l) {
                int best = l;
                for (int r = l; r < B; ++r) {
                    if (delta[r] < delta[best]) best = r;
                    inBlock[t][l][r] = best;
                }
            }
        }
    }

    void buildSparseTable() {
        lg.assign(nb + 1, 0);
        for (int i = 2; i <= nb; ++i) lg[i] = lg[i / 2] + 1;

        const int K = lg[nb] + 1;
        st.assign(K, vector<int>(nb, -1));
        for (int b = 0; b < nb; ++b) st[0][b] = blockMinIdx[b];

        for (int k = 1; k < K; ++k) {
            const int span = 1 << k;
            const int half = span >> 1;
            for (int i = 0; i + span - 1 < nb; ++i) {
                st[k][i] = betterIdx(st[k - 1][i], st[k - 1][i + half]);
            }
        }
    }

    void build(int root = 0) {
        euler.reserve(2 * n - 1);
        eulerDepth.reserve(2 * n - 1);
        dfs(root, -1, 0);
        m = (int)euler.size();

        int logm = (m > 1) ? (31 - __builtin_clz(m)) : 0;
        B = max(1, logm / 2);
        nb = (m + B - 1) / B;

        buildInBlockTables();

        blockId.assign(nb, 0);
        blockMinIdx.assign(nb, -1);
        for (int b = 0; b < nb; ++b) {
            int start = b * B;
            int end = min(m, start + B);
            int len = end - start;

            int mask = 0;
            for (int j = 0; j < B - 1; ++j) {
                int i1 = start + j;
                int i2 = start + j + 1;
                if (i2 < end) {
                    if (eulerDepth[i2] > eulerDepth[i1]) mask |= (1 << j);
                } else {
                    mask |= (1 << j);
                }
            }
            blockId[b] = mask;

            int rel = inBlock[mask][0][max(0, len - 1)];
            blockMinIdx[b] = start + rel;
        }

        buildSparseTable();
    }

    inline int rmqInBlock(int b, int lOff, int rOff) const {
        int start = b * B;
        int type = blockId[b];
        int rel = inBlock[type][lOff][rOff];
        return start + rel;
    }

    inline int rmqBlocks(int bl, int br) const {
        if (bl > br) return -1;
        int len = br - bl + 1;
        int k = lg[len];
        int i1 = st[k][bl];
        int i2 = st[k][br - (1 << k) + 1];
        return betterIdx(i1, i2);
    }

    int lca(int u, int v) const {
        int a = first[u];
        int b = first[v];
        if (a > b) swap(a, b);
        int ai = a / B;
        int bi = b / B;

        if (ai == bi) {
            int idx = rmqInBlock(ai, a % B, b % B);
            return euler[idx];
        }

        int best = rmqInBlock(ai, a % B, B - 1);

        int right = rmqInBlock(bi, 0, b % B);
        best = betterIdx(best, right);

        if (ai + 1 <= bi - 1) {
            int mid = rmqBlocks(ai + 1, bi - 1);
            best = betterIdx(best, mid);
        }

        return euler[best];
    }

    inline int dist(int u, int v) const {
        int w = lca(u, v);
        return depth[u] + depth[v] - 2 * depth[w];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    FCBLCA lca(n);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u;
        --u;
        v = i;
        lca.add_edge(u, v);
    }
    // Root can be any node; 0 (1 in 1-based) is conventional for CSES
    lca.build(0);

    while (q--) {
        int a, b; cin >> a >> b; --a; --b;
        cout << (lca.lca(a, b) + 1) << '\n';
    }
    return 0;
}
