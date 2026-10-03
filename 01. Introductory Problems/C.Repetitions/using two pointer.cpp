#include <bits/stdc++.h>
#define int long long
using namespace std;
 
signed main() {
    string s;
    cin >> s;
 
    int ans = 1;
    for (int i = 1,cnt = 1; i < s.size(); i++) {
        if (s[i] == s[i - 1]) {
            cnt++;
        } else {
            cnt = 1;
        }
        ans = max(ans, cnt);
    }
    cout << ans << endl;
    return 0;
}
