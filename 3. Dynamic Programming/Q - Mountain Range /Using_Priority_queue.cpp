#include <bits/stdc++.h>
#define int long long
using namespace std;
 
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> a(n);
    int ans = 1;
    for(int i = 0; i < n; ++i){
        cin >> a[i];
        int cnt = 1;
        while (pq.size() && pq.top().first < a[i]) {
            cnt = max(cnt + 1, pq.top().second + 1);
            pq.pop();
        }
        while(pq.size() && pq.top().first == a[i]){
            cnt = max(cnt, pq.top().second);
            pq.pop();
        }
        ans = max(ans, cnt);
        pq.push({a[i], cnt});
    }
    int cnt = 0;
    while(pq.size()){
        cnt = max(cnt + 1, pq.top().second + 1);
        pq.pop();
    }
    ans = max(ans, cnt - 1);
    cout << ans;
    return 0;
}

