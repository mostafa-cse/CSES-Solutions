#include <bits/stdc++.h>
#define int long long
using namespace std;
#define endl "\n"
#define all(x) x.begin(), x.end()
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n;
    cin >> n;
    struct time {
        int arrival, departure;
        int idx;
        bool operator<(time &other) const {
            return arrival < other.arrival;
        }
    };

    vector<time> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].arrival >> a[i].departure;
        a[i].idx = i;
    }
    sort(all(a));

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> allocation(n, 0);
    int room = 0;
    for (auto [x, y, i] : a) {
        if (!pq.empty() and pq.top().first < x) {
            int free = pq.top().second;
            pq.pop();
            allocation[i] = free;
            pq.push({y, free});
        } else {
            allocation[i] = ++room;
            pq.push({y, room});
        }
    }
    cout << room << endl;
    for (int i : allocation) {
        cout << i << " ";
    }
    return 0;
}
