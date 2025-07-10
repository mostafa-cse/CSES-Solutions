#include <bits/stdc++.h>
#define int long long
using namespace std;

int32_t main() {
    int n, m, k;
    cin >> n >> m >> k;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    priority_queue<int> best[n + 1];
    vector<pair<int, int>> adj[n + 1];
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }

    best[1].push(0);
    pq.push({0, 1});
    while (pq.size() > 0) {
        auto [dis, u] = pq.top();
        pq.pop();
        if (dis > best[u].top()) {
            continue;
        }
        for (auto [v, wt] : adj[u]) {
            int cur_dis = dis + wt;
            if (best[v].size() < k) {
                pq.push({cur_dis, v});
                best[v].push(cur_dis);
            } else if (cur_dis < best[v].top()) {
                best[v].pop();
                pq.push({cur_dis, v});
                best[v].push(cur_dis);
            }
        }
    }
    vector<int> ans;
    while (!best[n].empty()) {
        ans.push_back(best[n].top());
        best[n].pop();
    }
    reverse(ans.begin(), ans.end());
    for (auto a : ans)
        cout << a << " ";
    return 0;
}
