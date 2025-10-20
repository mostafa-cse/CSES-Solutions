#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 10;

int n;
vector<int> graph[MAXN];
int order[MAXN];
int subSize[MAXN];
int timer = 0;

void dfs(int u, int p) {
    order[u] = ++timer;
    subSize[u] = 1;
    for (auto v : graph[u]) {
        if (p != v) {
            dfs(v, u);
            subSize[u] += subSize[v];
        }
    }
}
int flatten[MAXN];
struct Query {
    int node_id;
    int left;
    int right;
} queries[MAXN];

int blockSize;
bool comp(const Query& a, const Query& b) {
    int block_a = a.left / blockSize;
    int block_b = b.left / blockSize;

    if (block_a != block_b) return block_a < block_b;
    if (block_a & 1) return a.right > b.right;
    return a.right < b.right;
}

int clr[MAXN];
int cnt = 0;
void add(int color) {
    clr[color]++;
    if (clr[color] == 1) cnt++;
}
void remove(int color) {
    clr[color]--;
    if (clr[color] == 0) cnt--;
}

int answer[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    blockSize = max(1, (int)sqrt(n));

    vector<int> color(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> color[i];
    }

    vector<int> comp(color.begin() + 1, color.end());
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    for (int i = 1; i <= n; i++) {
        color[i] = int(lower_bound(comp.begin(), comp.end(), color[i]) - comp.begin());
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(1, 0);
    for (int i = 1; i <= n; i++) {
        flatten[order[i]] = color[i];
    }

    for (int i = 1; i <= n; i++) {
        queries[i].node_id = i;
        queries[i].left = order[i];
        queries[i].right = order[i] + subSize[i] - 1;
    }

    sort(queries + 1, queries + n + 1, comp);
    int left_ptr = 1, right_ptr = 0;

    for (int i = 1; i <= n; i++) {
        while (right_ptr < queries[i].right) add(flatten[++right_ptr]);
        while (left_ptr > queries[i].left) add(flatten[--left_ptr]);
        while (right_ptr > queries[i].right) remove(flatten[right_ptr--]);
        while (left_ptr < queries[i].left) remove(flatten[left_ptr++]);
        answer[queries[i].node_id] = cnt;
    }

    for (int i = 1; i <= n; i++) {
        cout << answer[i] << (i < n ? ' ' : '\n');
    }
    return 0;
}
