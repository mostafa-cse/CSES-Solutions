#include <bits/stdc++.h>
#define int long long
using namespace std;
// Interval-Sweep + Min-Heap (O((n+m) log n))
int interval_heap(vector<int>& A, vector<int>& B, int k) {
    int n = A.size(), m = B.size();
    vector<pair<int, int>> intervals;
    intervals.reserve(n);
    for (int x : A)
        intervals.emplace_back(x - k, x + k);

    sort(intervals.begin(), intervals.end());
    sort(B.begin(), B.end());

    priority_queue<int, vector<int>, greater<int>> pq; // Min-heap for R
    int idx = 0, cnt = 0;

    for (int b : B) {
        while (idx < n && intervals[idx].first <= b) {
            pq.push(intervals[idx].second);
            idx++;
        }

        while (!pq.empty() && pq.top() < b) {
            pq.pop();
        }
        if (!pq.empty()) {
            pq.pop();
            cnt++;
        }
    }

    return cnt;
}
signed main() {
    int n, m;
    int k;
    cin >> n >> m >> k;
    vector<int> A(n), B(m);
    for (auto& x : A)
        cin >> x;
    for (auto& x : B)
        cin >> x;

    cout << interval_heap(A, B, k);
    return 0;
}