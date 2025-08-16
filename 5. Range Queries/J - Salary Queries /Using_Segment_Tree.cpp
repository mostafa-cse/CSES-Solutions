#include <bits/stdc++.h>
#define all(a) a.begin(), a.end()
using namespace std;
 
struct SegmentTree {
    vector<int> sgt;
    int n;
    SegmentTree(int N) {
        this->n = N + 1;
        sgt.assign(N * 4 + 1, 0);
    }
    int combine(int a, int b) {
        return a + b;
    }
    void update(int node, int l, int r, int idx, int value) {
        if (l == r) {
            sgt[node] += value;
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
            return 0; 
        }
        if (l >= ql and r <= qr) {
            return sgt[node];
        }
        int mid = l + (r - l) / 2;
        int left = query(node * 2, l, mid, ql, qr);
        int right = query(node * 2 + 1, mid + 1, r, ql, qr);
        return combine(left, right);
    }
    void update(int idx, int val) { update(1, 1, n, idx, val); }
    int query(int l, int r) { return query(1, 1, n, l, r); }
};

int main () {
    int n, q;
    cin >> n >> q;

    vector<int> ar(n), comp;
    for (int i = 0; i < n; i++) {
        cin >> ar[i];
        comp.push_back(ar[i]);
    }

    struct Query {
        char t;
        int a, b;
    };
    vector<Query> qr(q);

    for (int i = 0; i < q; i++) {
        cin >> qr[i].t >> qr[i].a >> qr[i].b;
        if (qr[i].t == '!') {
            qr[i].a--;
            comp.push_back(qr[i].b);
        } else {
            comp.push_back(qr[i].a);
            comp.push_back(qr[i].b);
        }
    }
    sort(all(comp));
    comp.resize(unique(comp.begin(), comp.end()) - comp.begin());

    function<int(int)> cast = [&](int x) -> int {
        return lower_bound(all(comp), x) - comp.begin() + 1; // make 1-based index
    };

    SegmentTree st(comp.size() + 1);
    for (int i : ar) {
        st.update(cast(i), 1);
    }
 
    for (auto &[t, a, b] : qr) {
        if (t == '!') {
            st.update(cast(ar[a]), -1);
            ar[a] = b;
            st.update(cast(ar[a]), 1);    
        } else {
            cout << st.query(cast(a), cast(b)) << '\n';
        }
    }
    return 0;
}