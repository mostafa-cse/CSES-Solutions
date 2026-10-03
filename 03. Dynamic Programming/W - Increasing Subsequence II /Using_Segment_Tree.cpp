#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

class SegTree
{
public:
    vector<int> tree;
    int n;
    SegTree(int n)
    {
        this->n = n;
        tree.resize(4 * n + 1);
    }
    void build(int index, int l, int r, vector<int> &a)
    {
        if (l == r)
        {
            tree[index] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(2 * index, l, mid, a);
        build(2 * index + 1, mid + 1, r, a);
        tree[index] = tree[2 * index] + tree[2 * index + 1];
    }
    void update(int index, int l, int r, int val, int pos)
    {
        if (pos < l || pos > r)
            return;
        if (l == r)
        {
            tree[index] = (tree[index] + val) % MOD;
            return;
        }
        int mid = (l + r) / 2;
        update(2 * index, l, mid, val, pos);
        update(2 * index + 1, mid + 1, r, val, pos);
        tree[index] = (tree[2 * index] + tree[2 * index + 1]) % MOD;
    }
    int query(int index, int lq, int rq, int l, int r)
    {
        if (lq > r || rq < l)
            return 0;
        if (lq <= l && r <= rq)
        {
            return tree[index];
        }
        int mid = (l + r) / 2;
        return (query(2 * index, lq, rq, l, mid) + query(2 * index + 1, lq, rq, mid + 1, r)) % MOD;
    }
};
signed main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    map<int, int> m;
    for (auto &i : a)
    {
        cin >> i;
        m[i];
    }
    int count = 0;
    for (auto &i : m)
    {
        i.second = count++;
    }
    
    SegTree st(count);
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        // index, ql, qr, l, r
        int sum = (m[a[i]] >= 1 ? st.query(1, 0, m[a[i]] - 1, 0, count) : 0);

        // index, l, r, val, pos
        st.update(1, 0, count, (1 + sum) % MOD, m[a[i]]);
        ans = (ans + (1 + sum)) % MOD;
    }
    cout << ans << endl;
    return 0;
}