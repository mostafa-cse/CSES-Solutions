#include <bits/stdc++.h>
#define int long long
using namespace std;
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
const int Mod = 1e9 + 7;
const int mod1 = 911382323, mod2 = 972663749;
const int p1 = 137, p2 = 139;
const int b1 = 137, b2 = 139, mxN = 5e6 + 10;
vector<int> pow_b1(mxN), pow_b2(mxN), inv_b1(mxN), inv_b2(mxN);
int modexpo(int a, int p,int mod){
    int res = 1;
    while(p){
        if(p&1){
            res = (a * res) % mod;
        }
        p >>= 1;
        a = (a * a) % mod;
    }
    return res;
}
void pre(){
    pow_b1[0] = pow_b2[0] = 1ll;
    for (int i = 1; i < mxN; ++i) {
        pow_b1[i] = (1ll * pow_b1[i - 1] * b1) % mod1;
        pow_b2[i] = (1ll * pow_b2[i - 1] * b2) % mod2;
    }
    inv_b1[mxN - 1] = modexpo(pow_b1[mxN - 1], mod1 - 2, mod1);
    inv_b2[mxN - 1] = modexpo(pow_b2[mxN - 1], mod2 - 2, mod2);
    for (int i = mxN - 2; i >= 0; i--) {
        inv_b1[i] = (1ll * inv_b1[i + 1] * b1) % mod1;
        inv_b2[i] = (1ll * inv_b2[i + 1] * b2) % mod2;
    }
};
struct StringHash {
    string str;
    vector<pair<int, int>> hsh;
    StringHash(string &s) : str(s), hsh(s.size() + 1, {0, 0}) {
        for (int i = 0; i < s.size(); i++) {
            if (i == 0) {
                hsh[i].first = (str[i] * pow_b1[i]) % mod1;
                hsh[i].second = (str[i] * pow_b2[i]) % mod2;
            } else {
                hsh[i].first = (hsh[i - 1].first + (str[i] * pow_b1[i]) % mod1) % mod1;
                hsh[i].second = (hsh[i - 1].second + (str[i] * pow_b2[i]) % mod2) % mod2;
            }
        }
    }
    pair<int, int> get(int l, int r) {
        if (l == 0) {
            return hsh[r];
        } else {
            int x = (hsh[r].first - hsh[l - 1].first + mod1) % mod1;
            x = (x * inv_b1[l]) % mod1;

            int y = (hsh[r].second - hsh[l - 1].second + mod2) % mod2;
            y = (y * inv_b2[l]) % mod2;
            return {x, y};
        }
    }
};
signed main() {
    pre();

    string s;
    cin >> s;
    StringHash sHash(s);

    int n;
    cin >> n;
    set<pair<int, int>> wordHshValue;
    set<int> len;
    for (int i = 0; i < n; i++) {
        string t;
        cin >> t;

        StringHash cur(t);
        wordHshValue.insert(cur.get(0, t.size() - 1));
    }

    n = s.size();
    vector<int> dp(n + 1, 0);
    dp[n] = 1;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i; j < n; j++) {
            pair<int, int> cur = sHash.get(i, j);

            if (wordHshValue.count(cur)) {
                dp[i] += dp[j + 1];
                dp[i] %= Mod;
            }
        }
    }
    cout << dp[0];
    return 0;
}
