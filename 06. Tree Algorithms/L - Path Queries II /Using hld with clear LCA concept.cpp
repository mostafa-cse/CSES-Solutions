#include <bits/stdc++.h>
using namespace std;
#define MAXN 2000006
class LCA {
    vector<vector<int>> p;
    vector<int> start, end, size;
    bool is_ancestor(int x, int y, vector<int> &start, vector<int> &end) {
        return start[x] <= start[y] && end[x] >= end[y];
    }
    int dfs(int x, vector<int> v[], int &k) {
        start[x] = k++;
        size[x] = 1;
        for (int i = 0; i < v[x].size(); i++) {
            if (v[x][i] != p[0][x]) {
                p[0][v[x][i]] = x;
                size[x] += dfs(v[x][i], v, k);
            }
        }
        end[x] = k;
        return size[x];
    }

public:
    LCA(vector<int> edge[], int n) {
        p = vector<vector<int>>(24, vector<int>(n));
        start = end = size = vector<int>(n, -1);
        int k = 0;
        dfs(0, edge, k);
        p[0][0] = 0;
        for (int k = 1; k < 24; k++) {
            for (int j = 0; j < n + 1; j++) {
                p[k][j] = p[k - 1][p[k - 1][j]];
            }
        }
    }
    int getLCA(int x, int y) {
        for (int k = 23; k >= 0; k--) {
            if (!is_ancestor(p[k][x], y, start, end)) {
                x = p[k][x];
            }
        }
        if (is_ancestor(x, y, start, end)) {
            return x;
        } else {
            return p[0][x];
        }
    }
    int getSize(int x) {
        return size[x];
    }
    int getParent(int x) {
        return p[0][x];
    }
};

class segmentTree {
    int tree[MAXN];
    int n;

    int op(int a, int b) {
        return max(a, b);
    }

    void buildTree(vector<int> a, int n) {
        for (int i = 0; i < n; i++) {
            tree[n + i] = a[i];
        }
        for (int i = n - 1; i > 0; i--) {
            tree[i] = op(tree[i << 1], tree[i << 1 | 1]);
        }
    }

public:
    segmentTree(vector<int> a, int n) {
        this->n = n;
        buildTree(a, n);
    }
    void updateTree(int p, int value) {
        tree[p + n] = value;
        p += n;
        for (int i = p; i > 1; i >>= 1) {
            tree[i >> 1] = op(tree[i], tree[i ^ 1]);
        }
    }

    int queryTree(int l, int r) {
        int res = INT_MIN;
        r++;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                res = op(res, tree[l++]);
            }
            if (r & 1) {
                res = op(res, tree[--r]);
            }
        }
        return res;
    }
};

class HLD
{
    int chainID, p;
    vector<int> nChain, chainHead, pos;
    vector<int> tree;
    LCA *lca;
    segmentTree *sg;

    void constructHLD(int x, int par, vector<int> edge[], vector<int> &val) {
        int heavyChild = -1;
        nChain[x] = chainID;
        tree[p] = val[x];
        pos[x] = p++;
        for (int i : edge[x]) {
            if (i != par) {
                if (heavyChild == -1) {
                    heavyChild = i;
                }
                if (lca->getSize(heavyChild) < lca->getSize(i)) {
                    heavyChild = i;
                }
            }
        }
        if (heavyChild != -1) {
            constructHLD(heavyChild, x, edge, val);
        }
        for (int i : edge[x]) {
            if (i != par && i != heavyChild) {
                chainID++;
                chainHead[chainID] = i;
                constructHLD(i, x, edge, val);
            }
        }
    }

    int queryUp(int from, int to) {
        int curr = from;
        int ans = 0;
        while (nChain[curr] != nChain[to]) {
            ans = max(ans, sg->queryTree(pos[chainHead[nChain[curr]]], pos[curr]));
            curr = lca->getParent(chainHead[nChain[curr]]);
        }
        ans = max(ans, sg->queryTree(pos[to], pos[curr]));
        return ans;
    }

public:
    HLD(vector<int> edge[], vector<int> &val, int n) {
        chainID = 1;
        p = 0;
        nChain = pos = chainHead = vector<int>(n, -1);
        tree = vector<int>(n, 0);
        lca = new LCA(edge, n);
        constructHLD(0, -1, edge, val);
        sg = new segmentTree(tree, n);
    }

    void update(int p, int val) {
        sg->updateTree(pos[p], val);
    }
    int query(int x, int y) {
        int t = lca->getLCA(x, y);
        int m = 0;
        m = max(m, queryUp(x, t));
        m = max(m, queryUp(y, t));
        return m;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q, x, y;
    cin >> n >> q;

    vector<int> val(n);
    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }

    vector<int> edge[n];
    for (int i = 0; i < n - 1; i++) {
        cin >> x >> y;
        edge[x - 1].push_back(y - 1);
        edge[y - 1].push_back(x - 1);
    }

    HLD hld(edge, val, n);
    int c;
    for (int i = 0; i < q; i++) {
        cin >> c;
        if (c == 1) {
            cin >> x >> y;
            hld.update(x - 1, y);
        } else {
            cin >> x >> y;
            cout << hld.query(x - 1, y - 1) << ' ';
        }
    }
    cout << endl;
    return 0;
}
