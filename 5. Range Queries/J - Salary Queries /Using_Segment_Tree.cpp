#include <bits/stdc++.h>
#define all(a) a.begin(), a.end()
using namespace std;

struct SegmentTree {
    int size;
    vector<int> tree;

    SegmentTree(int n) {
        size = 1;
        while (size < n) size <<= 1;
        tree.assign(2 * size, 0);
    }

    void update(int i, int val, int x, int lx, int rx) {
        if (rx - lx == 1) {
            tree[x] += val;
            return;
        }
        int mid = (lx + rx) / 2;
        if (i < mid)
            update(i, val, 2 * x + 1, lx, mid);
        else
            update(i, val, 2 * x + 2, mid, rx);
        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }

    void update(int i, int val) {
        update(i, val, 0, 0, size);
    }

    int query(int l, int r, int x, int lx, int rx) {
        if (rx <= l || lx >= r) return 0;
        if (lx >= l && rx <= r) return tree[x];
        int mid = (lx + rx) / 2;
        return query(l, r, 2 * x + 1, lx, mid) + query(l, r, 2 * x + 2, mid, rx);
    }

    int query(int l, int r) {
        return query(l, r + 1, 0, 0, size);
    }
};

int n, q;
vector<int> arr;
vector<pair<int, int>> comp;

int cast(int x) {
    return lower_bound(all(comp), pair<int, int>(x, 0))->second;
}

struct Query {
    char t;
    int a, b;
    void execute(SegmentTree &st) {
        if (t == '!') {
            st.update(cast(arr[a]), -1);
            arr[a] = b;
            st.update(cast(arr[a]), 1);
        } else {
            cout << st.query(cast(a), cast(b)) << '\n';
        }
    }
};

vector<Query> qr;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    arr.resize(n);

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        comp.push_back({arr[i], 0});
    }

    for (int i = 0; i < q; i++) {
        char t;
        int a, b;
        cin >> t >> a >> b;
        if (t == '!') {
            a--;
            comp.push_back({b, 0});
        } else {
            comp.push_back({a, 0});
            comp.push_back({b, 0});
        }
        qr.push_back({t, a, b});
    }

    sort(all(comp));

    for (int i = 0; i < comp.size(); ++i) {
        comp[i].second = i;
    }

    SegmentTree st((int)comp.size());

    for (int i = 0; i < n; i++) {
        st.update(cast(arr[i]), 1);
    }

    for (Query &it : qr) {
        it.execute(st);
    }

    return 0;
}
