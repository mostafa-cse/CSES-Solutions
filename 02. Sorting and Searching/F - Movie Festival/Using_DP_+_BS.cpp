#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;

    vector<pair<int, int>> I(n);
    for (int i = 0; i < n; i++) {
        cin >> I[i].first >> I[i].second;
    }

    sort(I.begin(), I.end(), [](const pair<int, int> &x, const pair<int, int> &y) { 
        return x.first < y.first; 
    });
    
    vector<int> ends(n), nxt(n);
    for (int i = 0; i < n; i++) {
        ends[i] = I[i].first;
    }

    for (int i = 0; i < n; i++) {
        // find first j with I[j].first >= I[i].second
        nxt[i] = lower_bound(ends.begin(), ends.end(), I[i].second) - ends.begin();
    }
    
    vector<int> dp(n+1,0);
    for (int i = n - 1; i >= 0; i--) {
        dp[i] = max(dp[i + 1], 1 + (nxt[i] < n ? dp[nxt[i]] : 0));
    }
    cout << dp[0];
    return 0;
}