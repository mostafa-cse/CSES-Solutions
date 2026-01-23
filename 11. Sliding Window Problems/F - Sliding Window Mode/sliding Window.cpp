#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int &i : a) {
        cin >> i;
    }

    // Counting Occurence
    map<int, int> cnt;

    // store result for max occurences and min value = {occur, -val}
    set<pair<int, int>> st;

    function<void(int x)> add = [&](int x) -> void {
        if (cnt[x] > 0) {
            st.erase({cnt[x], -x});
        }
        cnt[x]++;
        st.insert({cnt[x], -x});
    };

    function<void(int)> remove = [&](int x) -> void {
        st.erase({cnt[x], -x});
        cnt[x]--;

        if (cnt[x] > 0) {
            st.insert({cnt[x], -x});
        }
    };

    function<int()> query = [&]() -> int {
        int ret = -st.rbegin()->second;
        return ret;
    };

    for (int i = 0; i < n; i++) {
        add(a[i]);
        if (i + 1 >= k) {
            cout << query() << " ";
            remove(a[i - k + 1]);
        }
    }
    return 0;
}

