#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define int long long

// Use pair<int, int> to handle duplicates safely {value, unique_index}
typedef pair<int, int> pii;
#define ordered_set tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update>

struct FenwickTree {
    vector<int> bit;
    int n;

    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, 0);
    }

    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    int sum(int l, int r) {
        if (l > r) return 0;
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};

struct CoordCompressor {
    vector<int> coords;
    void add(int x) { coords.push_back(x); }
    void build() {
        sort(coords.begin(), coords.end());
        coords.erase(unique(coords.begin(), coords.end()), coords.end());
    }
    int get(int x) {
        return lower_bound(coords.begin(), coords.end(), x) - coords.begin();
    }
    int size() { return coords.size(); }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;


    CoordCompressor a;
    vector<int> ar(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> ar[i];
        a.add(ar[i]);
    }
    a.build();

    int max_val = a.size();
    FenwickTree S(max_val + 5), cnt(max_val + 5);
    ordered_set st;

    for (int i = 1; i <= n; i++) {
        st.insert({ar[i], i});

        int pos_add = a.get(ar[i]);
        S.add(pos_add, ar[i]);
        cnt.add(pos_add, 1);

        if (i >= k) {
            int median = st.find_by_order((k - 1) / 2)->first;
            int pos = a.get(median);

            int ans = 0;

            int cntLess = cnt.sum(0, pos);
            int sumLess = S.sum(0, pos);
            ans += (cntLess * median) - sumLess;

            int cntGreater = cnt.sum(pos, max_val);
            int sumGreater = S.sum(pos, max_val);
            ans += sumGreater - (cntGreater * median);

            cout << ans << " ";
            st.erase({ar[i - k + 1], i - k + 1});

            int pos_remove = a.get(ar[i - k + 1]);
            S.add(pos_remove, -ar[i - k + 1]);
            cnt.add(pos_remove, -1);
        }
    }
    return 0;
}
