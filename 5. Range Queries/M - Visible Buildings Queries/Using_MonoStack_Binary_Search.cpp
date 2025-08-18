#include <bits/stdc++.h>
using namespace std;
#define int long long

struct Query {
    int l, r;
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, Q;
    cin >> n >> Q;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<int> queriesAtL[n + 1]; // store queries grouped by left endpoint
    vector<Query> ques(Q + 1);
    for (int i = 1; i <= Q; i++) {
        cin >> ques[i].l >> ques[i].r;
        queriesAtL[ques[i].l].push_back(i);
    }

    int l = n * 2 + 1, r = n * 2; // empty deque initially

    // Process from right to left
    int que[n * 2 + 1], ans[n + 1];
    for (int i = n; i >= 1; i--) {
        // Maintain decreasing stack of indices in que[]
        while (l <= r && a[que[l]] <= a[i]) l++;
        que[--l] = i;

        // Answer queries that start at i
        for (int qid : queriesAtL[i]) {
            int right = ques[qid].r;
            int id = upper_bound(que + l, que + r + 1, right) - que;
            id--;
            ans[qid] = id - l + 1;
        }
    }
    for (int i = 1; i <= Q; i++) cout << ans[i] << "\n";
    return 0;
}
