#include <bits/stdc++.h>
#define int long long
using namespace std;
string a, b;
int dp[20][2][2][12][2];
 
int digitdp(int idx, bool lasta, bool lastb, int prev, bool started) {
    if (idx == a.size()) {
        return 1;
    }
    int &res = dp[idx][lasta][lastb][prev+1][started];
    if(res != -1) return res;
    
    int lb = (lasta ? a[idx] : '0') - '0';
    int ub = (lastb ? b[idx] : '9') - '0';
    int ans = 0;
    
    for (int d = lb; d <= ub; d++) {
        if (started && d == prev)
            continue;
        bool newStarted = started || (d != 0);
        ans += digitdp(idx + 1, lasta && (d == lb), lastb && (d == ub), newStarted ? d : -1, newStarted);
    }
    return res = ans;
}

int call (int x, int y) {
    int ans = 0;
    if (x <= 10 && y <= 10) return y - x + 1;
    else if (x < 10) {
        ans = 10 - x;
        x = 10;
    }
    a = to_string(x);
    b = to_string(y);
    while(a.size() < b.size()) {
        a = '0' + a;
    }
    memset(dp, -1, sizeof(dp));
    return digitdp(0, true, true, -1, false) + ans;
}
 
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int x, y;
    cin >> x >> y;
    cout << call(x, y);
    return 0;
}