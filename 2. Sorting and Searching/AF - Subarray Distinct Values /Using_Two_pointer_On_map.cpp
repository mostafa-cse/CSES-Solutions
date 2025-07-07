#include<bits/stdc++.h>
#define int long long
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);  cout.tie(0);
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int &i : a) {
        cin >> i;
    }

    int ans = 0, distinct = 0, left = 0;
    map<int, int> cnt;
    for (int i = 0; i < n; ++i) {
        if (cnt[a[i]] == 0) {
            distinct++;
        }
        cnt[a[i]]++;
        while (distinct > k) {
            cnt[a[left]]--;
            if (cnt[a[left]] == 0) {
                distinct--;
            }
            left++;
        }
        ans += i - left + 1;
    }
    cout << ans;
    return 0;
}
