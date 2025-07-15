#include <bits/stdc++.h>
#define int long long
using namespace std;

struct Query {
    int l, r, idx;
};

int BLOCK;

bool cmp(const Query &a, const Query &b) {
    int block_a = a.l / BLOCK;
    int block_b = b.l / BLOCK;
    if (block_a != block_b) return block_a < block_b;
    return (block_a & 1) ? (a.r < b.r) : (a.r > b.r);
}

signed main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    BLOCK = sqrt(n) + 1;
    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].idx = i;
    }
    sort(queries.begin(), queries.end(), cmp);
    vector<int> ans(q);
    multiset<int> window;
    int curr_l = 1, curr_r = 0;
    for (auto &query : queries) {
        int l = query.l, r = query.r;
        while (curr_r < r) {
            curr_r++;
            window.insert(a[curr_r]);
        }
        while (curr_r > r) {
            window.erase(window.find(a[curr_r]));
            curr_r--;
        }
        while (curr_l < l) {
            window.erase(window.find(a[curr_l]));
            curr_l++;
        }
        while (curr_l > l) {
            curr_l--;
            window.insert(a[curr_l]);
        }
        ans[query.idx] = *window.begin();
    }
    for (int i = 0; i < q; i++) cout << ans[i] << '\n';
    return 0;
}
