#include <bits/stdc++.h>
#define int long long
using namespace std;
const int Mod = 1e9 + 7;
signed main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int ans = 0;
    map<int, int> cnt;
    for (int l = 0, r = 0; l < n; l++) {
        while (r < n and cnt.count(a[r]) == 0) {
            cnt[a[r]]++;
            r++;
        }
        
    }
    return 0;
}