/*
SACK
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 200001;
int n, k;
vector<int> g[N];
long long answer;

void merge(deque<int> &a, deque<int> &b) {
    if (b.size() > a.size()) {
        swap(a, b);
    }
    int bs = b.size();
    for (int i = 0; i < bs; ++i) {
        if (0 <= k - i && k - i < (int)a.size()) {
            answer += b[i] * a[k - i];
        }
    }
    for (int i = 0; i < bs; ++i) {
        a[i] += b[i]; // resize the depth of each node
    }
}

deque<int> dfs(int node, int parent) {
    deque<int> ret{1};
    for (int child : g[node]) {
        if (child != parent) {
            auto child_depths = dfs(child, node);
            child_depths.push_front(0);
            merge(ret, child_depths);
        }
    }
    return ret;
}

int main() {
    cin >> n >> k;

    for (int i = 1; i <= n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(1, -1);
    cout << answer << '\n';
}
