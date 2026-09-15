#include <bits/stdc++.h>
#define int long long
using namespace std;
#define endl "\n"
#define all(x) x.begin(), x.end()
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int &i : a) cin >> i;

    struct info {
        int val;
        int cnt;
        bool operator<(const info other) const {
            if (cnt == other.cnt) return val < other.val;
            return cnt > other.cnt;
        }
    };
    map<int, int> cnt;
    set<info> st;

    for (int i = 0; i < n; i++) {
        if (cnt.count(a[i])) {
            st.erase({a[i], cnt[a[i]]});
            cnt[a[i]]++;
            st.insert({a[i], cnt[a[i]]});
        } else {
            cnt[a[i]]++;
            st.insert({a[i], cnt[a[i]]});
        }

        if (i + 1 >= k) {
            cout << st.begin()->val << " ";
            st.erase({a[i - k + 1], cnt[a[i - k + 1]]});
            --cnt[a[i - k + 1]];
            if (cnt[a[i - k + 1]] > 0) {
                st.insert({a[i - k + 1], cnt[a[i - k + 1]]});
            }
        }
    }
    return 0;
}
