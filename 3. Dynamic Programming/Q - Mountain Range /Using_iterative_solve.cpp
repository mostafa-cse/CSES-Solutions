#include <bits/stdc++.h>
using namespace std;
#define int long long
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int n;
    cin >> n;
    vector<int> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];
 
    // L[i] = index of nearest taller mountain to the left of i
    // R[i] = index of nearest taller mountain to the right of i
    vector<int> L(n, -1), R(n, -1);
    stack<int> st;
 
    // Nearest greater to left
    for (int i = 0; i < n; i++) {
        while (!st.empty() && h[st.top()] <= h[i])
            st.pop();
        if (!st.empty()) L[i] = st.top();
        st.push(i);
    }
 
    // Clear stack
    while (!st.empty()) st.pop();
 
    // Nearest greater to right
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && h[st.top()] <= h[i])
            st.pop();
        if (!st.empty()) R[i] = st.top();
        st.push(i);
    }
 
    // DP: process from tallest to shortest mountain
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int a, int b) {
        return h[a] > h[b];
    });
 
    vector<int> dp(n, 1);
    int ans = 1;
    for (int i : idx) {
        if (L[i] != -1) dp[i] = max(dp[i], 1 + dp[L[i]]);
        if (R[i] != -1) dp[i] = max(dp[i], 1 + dp[R[i]]);
        ans = max(ans, dp[i]);
    }
 
    cout << ans << '\n';
    return 0;
}