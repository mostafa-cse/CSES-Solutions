#include<bits/stdc++.h>
#define int long long int 
using namespace std;

int32_t main() {
    int n; cin >> n;
    vector<int> arr(n); for (int i = 0; i < n; i++) cin >> arr[i];
 
    stack<int> st;
    vector<int> frm1(n, -1), frm2(n, -1);
    for (int i = 0; i < n; i++) {
        while (st.size() > 0 && arr[st.top()] <= arr[i]) {
            st.pop();
        }
 
        if (st.size() == 0) {
            st.push(i);
            continue;
        }
 
        frm1[i] = st.top();
        st.push(i);
    }
 
    while (st.size()) st.pop();
 
    for (int i = n - 1; i >= 0; i--) {
        while (st.size() > 0 && arr[st.top()] <= arr[i]) {
            st.pop();
        }
 
        if (st.size() == 0) {
            st.push(i);
            continue;
        } 
        frm2[i] = st.top();
        st.push(i);
    }
 
    priority_queue<pair<int, int>> pq;
 
    for (int i = 0; i < n; i++) pq.emplace(arr[i], i);
    int ans = 0;
    vector<int> dp(n, 1);
    while (pq.size() > 0) {
        auto [_, idx] = pq.top();
        pq.pop();
 
        if (frm1[idx] != -1) {
            dp[idx] = max(dp[idx], dp[frm1[idx]] + 1);
        }
 
        if (frm2[idx] != -1) {
            dp[idx] = max(dp[idx], dp[frm2[idx]] + 1);
        }
        ans = max(ans, dp[idx]);
    }
 
    cout << ans << endl;
    return 0;
}