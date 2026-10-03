#include<bits/stdc++.h>
#define int long long
using namespace std;
const int Mod = 1e9+7;

int32_t main() {
    string s;
    cin >> s;
    s = s;

    map<char, int> cnt;
    for (char c : s) {
        int sum = 1;
        for (auto [ch, occ] : cnt) {
            sum += occ;
            sum %= Mod;
        }
        cnt[c] = sum ;
    }

    int ans = 0;
    for (auto [ch, occ] : cnt) {
        ans += occ;
        ans %= Mod;
    }
    cout << ans << endl;
    return 0;
}
