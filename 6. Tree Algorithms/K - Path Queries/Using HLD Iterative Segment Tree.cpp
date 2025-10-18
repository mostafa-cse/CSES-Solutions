#include <bits/stdc++.h>
using namespace std;
struct SumNode {
    long long sum;
    SumNode(long long v) { sum = v; }
    SumNode() { sum = 0; }
    SumNode(const SumNode& left, const SumNode& right) { sum = left.sum + right.sum; }
};
template <class Node, class T>
struct SegmentTree {
    vector<T> A;
    vector<Node> st;

    SegmentTree() {}
    SegmentTree(vector<T> A) {
        this->A = A;
        st.assign(A.size() * 2, Node());
        build();
    }

    void build() {
        for (int i = 0; i < A.size(); i++)
            st[i + A.size()] = Node(A[i]);
        for (int i = A.size() - 1; i > 0; i--)
            st[i] = Node(st[i << 1], st[i << 1 | 1]);
    }

    Node query(int l, int r) {
        Node res1, res2;
        for (l += A.size(), r += A.size(); l < r; l >>= 1, r >>= 1) {
            if (l & 1) res1 = Node(res1, st[l++]);
            if (r & 1) res2 = Node(st[--r], res2);
        }
        return Node(res1, res2);
    }

    void update(int p, T v) {
        for (st[p += A.size()] = Node(v); p > 1; p >>= 1)
            st[p >> 1] = Node(st[(p | 1) ^ 1], st[p | 1]);
    }
};

template <class Node, class T>
struct HeavyLight {
    vector<int> parent, heavy, depth, root, stPos;
    SegmentTree<Node, T> tree;

    int dfs(const vector<vector<int>>& graph, int v) {
        int size = 1, maxSubtree = 0;
        for (int u : graph[v]) {
            if (u != parent[v]) {
                parent[u] = v;
                depth[u] = depth[v] + 1;
                int subtree = dfs(graph, u);
                if (subtree > maxSubtree) heavy[v] = u, maxSubtree = subtree;
                size += subtree;
            }
        }
        return size;
    }

    HeavyLight(const vector<vector<int>>& graph, vector<T> A) {
        heavy.assign(A.size(), -1);
        parent.assign(A.size(), -1);
        depth.assign(A.size(), 0);
        root.assign(A.size(), 0);
        stPos.assign(A.size(), 0);
        dfs(graph, 0);
        vector<T> treeA(A.size());
        for (int i = 0, pos = 0; i < A.size(); i++) {
            if (parent[i] == -1 || heavy[parent[i]] != i) {
                for (int j = i; j != -1; j = heavy[j]) {
                    root[j] = i;
                    treeA[pos] = A[j];
                    stPos[j] = pos++;
                }
            }
        }
        tree = SegmentTree<Node, T>(treeA);
    }

    void update(int v, T val) {
        tree.update(stPos[v], val);
    }

    Node query(int u, int v) {
        Node res;
        for (; root[u] != root[v]; v = parent[root[v]]) {
            if (depth[root[u]] > depth[root[v]]) swap(u, v);
            res = Node(res, tree.query(stPos[root[v]], stPos[v] + 1));
        }
        if (depth[u] > depth[v]) swap(u, v);
        res = Node(res, tree.query(stPos[u], stPos[v] + 1));
        return res;
    }
};

int N, Q;
vector<long long> A;
vector<vector<int>> adj;

int main() {
    ios_base::sync_with_stdio(false);

    cin >> N >> Q;

    A.assign(N, 0);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    adj.assign(N, vector<int>());

    for (int i = 0; i < N - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a - 1].push_back(b - 1);
        adj[b - 1].push_back(a - 1);
    }

    HeavyLight<SumNode, long long> hd(adj, A);
    for (int i = 0; i < Q; i++) {
        int t; cin >> t;
        if (t == 1) {
            int s, x; cin >> s >> x;
            hd.update(s - 1, x);
        }
        else {
            int s; cin >> s;
            cout << hd.query(0, s - 1).sum << "\n";
        }
    }
    return 0;
}
