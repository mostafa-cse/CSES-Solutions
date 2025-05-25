#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    string s;
    cin >> s;

    function<bool(int)> fun = [&](int len) -> bool {
        map<char, int> cnt;
        for (int i = 0; i < s.size(); i++) {
            cnt[s[i]]++;
            if (i + 1 >= len) {
                if (cnt.size() == 1) {
                    return true;
                }
                
                cnt[s[i - len + 1]]--;
                if (cnt[s[i - len + 1]] == 0) {
                    cnt.erase(s[i - len + 1]);
                }
            }
        }
        return false;
    };

    int l = 1, r = s.size(), ans = 1;
    while (l <= r) {
        int mid = l + r >> 1;
        if (fun(mid)) {
            l = mid + 1;
            ans = mid;
        } else {
            r = mid - 1;
        }
    }
    cout << ans;
    return 0;
}
