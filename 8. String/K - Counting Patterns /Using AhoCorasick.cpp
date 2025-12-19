#include <bits/stdc++.h>
using namespace std;

struct AhoCorasick {
    static const int K = 26;

    struct Node {
        int nxt[K];
        int fail = 0;
        int count = 0;
        vector<int> ended_patterns;

        Node() { memset(nxt, 0, sizeof(nxt)); }
    };

    vector<Node> nodes;
    vector<int> bfs_order;

    AhoCorasick() {
        nodes.emplace_back();
    }

    void insert(const string& s, int id) {
        int u = 0;
        for (char c : s) {
            int i = c - 'a';
            if (!nodes[u].nxt[i]) {
                nodes[u].nxt[i] = nodes.size();
                nodes.emplace_back();
            }
            u = nodes[u].nxt[i];
        }
        nodes[u].ended_patterns.push_back(id);
    }

    void build() {
        queue<int> q;
        for (int i = 0; i < K; i++) {
            if (nodes[0].nxt[i]) q.push(nodes[0].nxt[i]);
        }

        while (!q.empty()) {
            int u = q.front(); q.pop();
            bfs_order.push_back(u);

            for (int i = 0; i < K; i++) {
                if (nodes[u].nxt[i]) {
                    nodes[nodes[u].nxt[i]].fail = nodes[nodes[u].fail].nxt[i];
                    q.push(nodes[u].nxt[i]);
                } else {
                    nodes[u].nxt[i] = nodes[nodes[u].fail].nxt[i];
                }
            }
        }
    }

    vector<int> query(const string& text, int num_patterns) {
        int u = 0;
        for (char c : text) {
            u = nodes[u].nxt[c - 'a'];
            nodes[u].count++;
        }

        for (int i = bfs_order.size() - 1; i >= 0; i--) {
            int u = bfs_order[i];
            int f = nodes[u].fail;
            nodes[f].count += nodes[u].count;
        }

        vector<int> ans(num_patterns);
        for (int i = 0; i < nodes.size(); i++) {
            for (int id : nodes[i].ended_patterns) {
                ans[id] = nodes[i].count;
            }
        }
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    string s;
    int q;
    cin >> s >> q;
    AhoCorasick ac;
    for (int i = 0; i < q; i++) {
        string p;
        cin >> p;
        ac.insert(p, i);
    }
    ac.build();

    vector<int> results = ac.query(s, q);

    for (int x : results) {
        cout << x << "\n";
    }
    return 0;
}
