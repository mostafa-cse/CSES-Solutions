#include <bits/stdc++.h>
using namespace std;

const int N = 200001;

int parent[N];
int depth[N];
int jump[N];
int jump_size[N];
vector<int> g[N];

void dfs(int node) {
    for (int child : g[node]) {
        depth[child] = depth[node] + 1;
        parent[child] = node;
        jump[child] = node;
        jump_size[child] = 1;
        if (jump[node] && jump[jump[node]] &&
            jump_size[node] == jump_size[jump[node]]) {
            jump[child] = jump[jump[node]];
            jump_size[child] = jump_size[node] * 2 + 1;
        }
        dfs(child);
    }
}

int make_jumps(int x, int k) {
    if (depth[x] < k) {
        return -1;
    }
    while (k) {
        if (jump_size[x] <= k) {
            k -= jump_size[x];
            x = jump[x];
        } else {
            k--;
            x = parent[x];
        }
    }
    return x;
}

int main() {
    int n, q;

    cin >> n >> q;

    for (int i = 2; i <= n; ++i) {
        int p;
        cin >> p;
        g[p].push_back(i);
    }

    dfs(1);

    for (int qi = 0; qi < q; ++qi) {
        int x, k;
        cin >> x >> k;

        cout << make_jumps(x, k) << '\n';
    }
}
