#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
const int inf = 1e15;
const int mod2 = 1e9 + 9;

const int N = 1000010;

class segtree {
public:
    int size;
    vector<int> node, lazy;

    int DEFAULT = 0;
    int NO_OP = inf;
    segtree(int n) {
        size = 1;
        while (size < n) {
            size *= 2;
        }
        node.assign(2 * size, 0);
        lazy.assign(2 * size, 0);
    }

    int operationAdd(int a, int b) {
        return a + b;
    }
    int operationMul(int a, int b, int len) {
        if (b == NO_OP)
            return a;
        return (b * len);
    }
    void apply_mul_op(int &a, int &b, int len) {
        a = operationMul(a, b, len);
    }

    void propagate(int x, int lx, int rx) {
        if (rx - lx == 1) {
            return;
        }
        int mid = lx + rx;
        mid /= 2;

        apply_mul_op(node[2 * x + 1], node[x], 1);
        apply_mul_op(node[2 * x + 2], node[x], 1);
        apply_mul_op(lazy[2 * x + 1], node[x], mid - lx);
        apply_mul_op(lazy[2 * x + 2], node[x], rx - mid);
        node[x] = NO_OP;
    }
    void modify(int l, int r, int v, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (r <= lx || rx <= l) {
            return;
        }

        if (l <= lx && rx <= r) {
            apply_mul_op(node[x], v, 1);
            apply_mul_op(lazy[x], v, rx - lx);
            return;
        }

        int m = lx + rx;
        m /= 2;

        modify(l, r, v, 2 * x + 1, lx, m);
        modify(l, r, v, 2 * x + 2, m, rx);

        lazy[x] = operationAdd(lazy[2 * x + 1], lazy[2 * x + 2]);
    }
    void modify(int l, int r, int v) {
        modify(l, r, v, 0, 0, size);
    }
    int getquery(int l, int r) {
        return getquery(l, r, 0, 0, size);
    }
    int getquery(int l, int r, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (l >= rx || lx >= r) {
            return DEFAULT;
        }

        if (l <= lx && rx <= r) {
            return lazy[x];
        }

        int mid = (lx + rx) / 2;
        auto s1 = getquery(l, r, 2 * x + 1, lx, mid);
        auto s2 = getquery(l, r, 2 * x + 2, mid, rx);
        return operationAdd(s1, s2);
    }
};

signed main() {
    int n, m;
    cin >> n >> m;


    int a[n + 1], pre[n + 1]{0};
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pre[i + 1] = pre[i] + a[i];
    }

    vector<vector<pair<int, int>>> que(n);
    for (int i = 0; i < m; i++){
        int l, r;
        cin >> l >> r;
        l--, r--;

        que[l].push_back({r, i});
    }

    stack<int> st;
    st.push(n);

    a[n] = inf;

    int ans[m];

    segtree stt(n);

    for (int l = n - 1; l >= 0; l--) {
        while (!st.empty() && a[st.top()] < a[l]) {
            st.pop();
        }
        stt.modify(l, st.top(), a[l]);
        st.push(l);
        for (auto &[r, idx] : que[l]) {
            ans[idx] = stt.getquery(l, r + 1) - pre[r + 1] + pre[l];
        }
    }

    for (int i = 0; i < m; i++)
        cout << ans[i] << "\n";
    return 0;
}
