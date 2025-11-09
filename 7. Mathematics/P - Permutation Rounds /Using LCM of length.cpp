// https://www.gauthmath.com/solution/d9j67MTUS3n/Prove-that-the-order-of-a-permutation-is-the-l-c-m-of-the-lengths-of-the-cycles-
#include <bits/stdc++.h>
#define int long long
using namespace std;
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
const int Mod = 1e9 + 7;
int modexpo(int a, int p,int mod) {
    int res = 1;
    while (p) {
        if(p & 1) {
            res = (a * res) % mod;
        }
        p >>= 1;
        a = (a * a) % mod;
    }
    return res;
}
signed main() {
    int n;
    cin >> n;

    vector<vector<int>> a(n + 1);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        a[i].push_back(x);
        a[x].push_back(i);
    }

    vector<int>vis(n + 1, 0);
    function<int(int)> dfs = [&](int u)-> int {
        int ans = 1;
        vis[u] = 1;
        for (int v : a[u]) {
            if (vis[v] == 0) {
                ans = 1 + dfs(v);
            }
        }
        return ans;
    };
    vector<int> cycleLen;
    for (int i = 1; i <= n; i++) {
        int len = dfs(i);
        if (len > 1) {
            cycleLen.push_back(len);
        }
    }

    map<int, int> cnt;
    for (int val : cycleLen) {
        for (int i = 2; i * i <= val; i++) {
            if (val % i == 0) {
                int pcnt = 0;
                while (val % i == 0) {
                    val /= i;
                    pcnt++;
                }
                cnt[i] = max(pcnt, cnt[i]);
            }
        }
        if (val != 1) {
            cnt[val] = max(cnt[val], 1ll);
        }
    }

    int ans = 1;
    for (auto [f, s] : cnt) {
        ans = (ans * modexpo(f, s, Mod)) % Mod;
    }
    cout << ans;
    return 0;
}
