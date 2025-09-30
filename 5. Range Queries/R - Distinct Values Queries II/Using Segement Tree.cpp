#include <bits/stdc++.h>
#define int long long
using namespace std;

struct SegmentTree {
    vector<int> sgt;
    vector<int> a;
    int n;
    SegmentTree(int N) {
        this->n = N;
        a.assign(N + 1, 0);
        sgt.assign(N * 4 + 1, 0);
    }
    int combine(int a, int b) {
        return min(a, b);
    }
    void build (int node, int l, int r) {
        if (l == r) {
            sgt[node] = a[l];
            return;
        }
        int mid = l + (r - l) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        sgt[node] = combine(sgt[2 * node], sgt[2 * node + 1]);
    }
    void update(int node, int l, int r, int idx, int value) {
        if (l == r) {
            sgt[node] = value;
            return;
        }
        int mid = l + (r - l) / 2;
        if(idx <= mid) {
            update(node * 2, l, mid, idx, value);
        } else {
            update(node * 2 + 1, mid + 1, r, idx, value);
        }
        sgt[node] = combine(sgt[2 * node], sgt[2 * node + 1]);
    }
    int query(int node, int l, int r, int ql, int qr) {
        if (l > qr or r < ql) {
            return 1e18; // Edit here
        }
        if (l >= ql and r <= qr) {
            return sgt[node];
        }
        int mid = l + (r - l) / 2;
        int left = query(node * 2, l, mid, ql, qr);
        int right = query(node * 2 + 1, mid + 1, r, ql, qr);
        return combine(left, right);
    }
    void build() { build(1, 1, n); }
    void update(int idx, int val) { update(1, 1, n, idx, val); }
    int query(int l, int r) { return query(1, 1, n, l, r); }
};
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    map<int, set<int>> valPos;
    vector<int> ar(n + 1);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        ar[i] = x;
        valPos[x].insert(i);
    }

    vector<int> next_arr(n + 1, n + 1);
    for (auto p : valPos) {
        set<int> &s = p.second;
        if (s.size() > 1) {
            auto it = s.begin();
            while (next(it) != s.end()) {
                next_arr[*it] = *next(it);
                ++it;
            }
        }
    }
    SegmentTree a(n);
    a.a = next_arr;

    a.build();
    while (q--) {
        int qt;
        cin >> qt;

        if (qt == 1) {
            int idx, val;
            cin >> idx >> val;
            // Keep 1-indexed for segment tree

            if (idx < 1 || idx > n) continue; // bounds check

            // step - 1: clear the history of previous value
            function<void()> erase = [&] () -> void {
                int old = ar[idx];
                set<int> &s = valPos[old];
                auto it = s.find(idx);

                int Pre = 0, Next = 0;
                if (it != s.begin()) {
                    auto tem = it;
                    --tem;
                    Pre = *tem;
                }

                auto tem = it; ++tem;
                if (tem != s.end()) Next = *tem;

                s.erase(it);
                if (s.empty()) valPos.erase(old);

                // rebuilt connection agin
                if (Pre != 0) {
                    next_arr[Pre] = (Next != 0 ? Next : n + 1);
                    a.update(Pre, next_arr[Pre]);
                }
                next_arr[idx] = n + 1;
                a.update(idx, next_arr[idx]);
            };
            erase();

            // step - 2: insert a new value
            function<void()> Insert = [&]() -> void {
                ar[idx] = val;
                set<int> &s = valPos[val];

                auto it = s.lower_bound(idx);
                int Pre = 0, Next = 0;
                if (it != s.begin()) {
                    auto prev_it = prev(it);
                    Pre = *prev_it;
                }

                if (it != s.end()) Next = *it; // current place will be next

                s.insert(idx);

                // connection built agin after insert
                if (Pre != 0) {
                    next_arr[Pre] = idx;
                    a.update(Pre, idx);
                }
                next_arr[idx] = Next != 0 ? Next : n + 1;
                a.update(idx, next_arr[idx]);
            };
            Insert();
        } else {
            int l, r;
            cin >> l >> r;
            // Keep 1-indexed for segment tree

            if (l < 1 || r > n || l > r) {
                cout << "YES" << endl;
                continue;
            }

            int next = a.query(l, r);

            if (next > r) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }

    return 0;
}
