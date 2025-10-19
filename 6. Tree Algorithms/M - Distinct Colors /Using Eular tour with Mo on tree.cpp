#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 10;

int n;
vector<int> graph[MAXN];
int dfn_order[MAXN];
int subtree_size[MAXN];
int timer = 0;

void compute_euler_tour_iterative(int root) {
    vector<int> parent(n + 1, 0), itIndex(n + 1, 0);
    stack<int> st;
    st.push(root);
    parent[root] = 0;

    while (!st.empty()) {
        int v = st.top();
        if (itIndex[v] == 0) {
            dfn_order[v] = ++timer;
            subtree_size[v] = 1;
        }
        if (itIndex[v] < (int)graph[v].size()) {
            int u = graph[v][itIndex[v]++];
            if (u == parent[v]) continue;
            parent[u] = v;
            st.push(u);
        } else {
            st.pop();
            if (parent[v]) subtree_size[parent[v]] += subtree_size[v];
        }
    }
}

int flattened_colors[MAXN];

struct Query {
    int node_id;
    int left;
    int right;
} queries[MAXN];

int block_size;
bool mo_comparator(const Query& a, const Query& b) {
    int block_a = a.left / block_size;
    int block_b = b.left / block_size;

    if (block_a != block_b) return block_a < block_b;
    if (block_a & 1) return a.right > b.right;
    return a.right < b.right;
}

int color_frequency[MAXN];
int distinct_count = 0;
void add_color(int color) {
    color_frequency[color]++;
    if (color_frequency[color] == 1) distinct_count++;
}
void remove_color(int color) {
    color_frequency[color]--;
    if (color_frequency[color] == 0) distinct_count--;
}

int answer[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    block_size = max(1, (int)sqrt(n));

    vector<int> color(n + 1);
    for (int i = 1; i <= n; i++) cin >> color[i];

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

    compute_euler_tour_iterative(1);

    for (int i = 1; i <= n; i++) {
        flattened_colors[dfn_order[i]] = color[i];
    }

    for (int i = 1; i <= n; i++) {
        queries[i].node_id = i;
        queries[i].left = dfn_order[i];
        queries[i].right = dfn_order[i] + subtree_size[i] - 1;
    }

    sort(queries + 1, queries + n + 1, mo_comparator);

    int left_ptr = 1, right_ptr = 0;

    for (int i = 1; i <= n; i++) {
        while (right_ptr < queries[i].right) add_color(flattened_colors[++right_ptr]);
        while (left_ptr > queries[i].left) add_color(flattened_colors[--left_ptr]);
        while (right_ptr > queries[i].right) remove_color(flattened_colors[right_ptr--]);
        while (left_ptr < queries[i].left) remove_color(flattened_colors[left_ptr++]);
        answer[queries[i].node_id] = distinct_count;
    }

    for (int i = 1; i <= n; i++) {
        cout << answer[i] << (i < n ? ' ' : '\n');
    }
    return 0;
}
