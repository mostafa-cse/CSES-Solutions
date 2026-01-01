#include <bits/stdc++.h>
#define int long long
#define ff first
#define ss second
#define all(x) x.begin(), x.end()
#define pb push_back
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
struct ImplicitTreap {
    struct Node {
        int prior;
        int sz;
        int val;
        int sum;
        int lazy;
        bool rev;
        Node *l, *r;
        Node(int _v = 0) : prior(rng()), sz(1), val(_v), sum(_v), lazy(0), rev(false), l(nullptr), r(nullptr) {}
    };

    using pnode = Node *;
    pnode root = nullptr;

    static int getSize(pnode t) {
        return t ? t->sz : 0;
    }

    static int getSum(pnode t) {
        return t ? t->sum : 0;
    }

    void apply_rev(pnode t) {
        if (!t) return;
        t->rev ^= true;
        swap(t->l, t->r);
    }

    void apply_add(pnode t, int add) {
        if (!t) return;
        t->val += add;
        t->sum += add * getSize(t);
        t->lazy += add;
    }

    void push(pnode t) {
        if (!t) return;
        if (t->rev) {
            apply_rev(t->l);
            apply_rev(t->r);
            t->rev = false;
        }
        if (t->lazy != 0) {
            apply_add(t->l, t->lazy);
            apply_add(t->r, t->lazy);
            t->lazy = 0;
        }
    }

    void pull(pnode t) {
        if (!t) return;
        t->sz = 1 + getSize(t->l) + getSize(t->r);
        t->sum = t->val + getSum(t->l) + getSum(t->r);
    }

    void split(pnode t, pnode &l, pnode &r, int cnt) {
        if (!t) {
            l = r = nullptr;
            return;
        }
        push(t);
        int lsz = getSize(t->l);
        if (cnt <= lsz) {
            split(t->l, l, t->l, cnt);
            r = t;
            pull(r);
        } else {
            split(t->r, t->r, r, cnt - lsz - 1);
            l = t;
            pull(l);
        }
    }

    void merge(pnode &t, pnode l, pnode r) {
        if (!l || !r) {
            t = l ? l : r;
            return;
        }
        push(l);
        push(r);
        if (l->prior > r->prior) {
            merge(l->r, l->r, r);
            t = l;
            pull(t);
        } else {
            merge(r->l, l, r->l);
            t = r;
            pull(t);
        }
    }

    void insert(int pos, int v) {
        pnode a, b;
        split(root, a, b, pos);
        pnode cur = new Node(v);
        merge(a, a, cur);
        merge(root, a, b);
    }

    void build(const vector<int> &a) {
        root = nullptr;
        for (size_t i = 0; i < a.size(); ++i) {
            merge(root, root, new Node(a[i]));
        }
    }

    void reverse(int l, int r) {
        pnode a, b, c;
        split(root, a, b, l);
        split(b, b, c, r - l + 1);
        apply_rev(b);
        merge(b, b, c);
        merge(root, a, b);
    }

    int query(int l, int r) {
        pnode a, b, c;
        split(root, a, b, l);
        split(b, b, c, r - l + 1);

        int ans = getSum(b);

        merge(b, b, c);
        merge(root, a, b);
        return ans;
    }

    void add_val_in_range(int l, int r, int x) {
        pnode a = nullptr, b = nullptr, c = nullptr;
        split(root, a, b, l - 1);
        split(b, b, c, r - l + 1);

        apply_add(b, x);

        merge(b, b, c);
        merge(root, a, b);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<int> v(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i];
    }

    ImplicitTreap tr;
    tr.build(v);

    while (m--) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r;
            cin >> l >> r;
            tr.reverse(l - 1, r - 1);
        } else if (t == 2) {
            int l, r;
            cin >> l >> r;
            cout << tr.query(l - 1, r - 1) << "\n";
        }
        else if (t == 3) {
            int l, r, x;
            cin >> l >> r >> x;

        }
    }
    return 0;
}
