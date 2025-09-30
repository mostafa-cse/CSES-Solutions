#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("O3,unroll-loops")
#include <ext/pb_ds/assoc_container.hpp>
#pragma GCC target_options("arch=native,tune=native")
using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct SegTree {
    vector<int> s;

    SegTree (int n) {
        s.assign(4*n+10, 0);
    }

    void update (int i, int st, int en, int pos, int val) {
        if (st == en) {
            s[i] = val;
            return;
        }
        int mid = (st+en)/2;
        if (pos <= mid) update(2*i, st, mid, pos, val);
        else update(2*i+1, mid+1, en, pos, val);
        s[i] = max(s[2*i], s[2*i+1]);
    }

    int query (int i, int st, int en, int l, int r) {
        if (st > r || en < l) return 0;
        if (st >= l && en <= r) return s[i];
        int mid = (st+en)/2;
        return max(query(2*i, st, mid, l, r), query(2*i+1, mid+1, en, l, r));
    }
};
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n, q;
    cin >> n >> q;
    SegTree st(n);
    map<int, ordered_set<int>> pos;
    for (int i=1; i<=n; i++) {
        int val;
        cin >> val;
        if (pos[val].empty()) st.update(1, 1, n, i, val);
        pos[val].insert(i);
    }

    for (int i=0; i<q; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            int pos_idx, val;
            cin >> pos_idx >> val;

            // remove previous type
            int prev = -1;
            for (auto &p : pos) {
                auto it = p.second.find(pos_idx);
                if (it != p.second.end()) {
                    prev = p.first;
                    if (pos_idx == *p.second.begin()) st.update(1, 1, n, pos_idx, 0);
                    p.second.erase(pos_idx);
                    break;
                }
            }

            // insert new value
            if (pos[val].empty()) st.update(1, 1, n, pos_idx, val);
            else if (pos_idx < *pos[val].begin()) st.update(1, 1, n, pos_idx, val);
            pos[val].insert(pos_idx);
        }
        else {
            int l, r;
            cin >> l >> r;
            int ans = st.query(1, 1, n, l, r);
            if (ans == 0) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
    }
    return 0;
}
