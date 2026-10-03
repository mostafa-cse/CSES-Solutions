#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m;
vector<int> a;
vector<pair<int, int>> q;
vector<int> t, ps;
void push(int v, int l, int r) {
    if (v * 2 + 1 < t.size()) {
        ps[v * 2] += ps[v];
        ps[v * 2 + 1] += ps[v];
    }
    t[v] += ps[v] * (r - l);
    ps[v] = 0;
}

void upd(int v, int l, int r, int L, int R, int val) {
    push(v, l, r);
    if (L >= R) {
        return;
    }
    if (l == L && r == R) {
        ps[v] += val;
        push(v, l, r);
        return;
    }
    int m = (l + r) / 2;
    upd(v * 2, l, m, L, min(m, R), val);
    upd(v * 2 + 1, m, r, max(m, L), R, val);
    t[v] = t[v * 2] + t[v * 2 + 1];
}

int get(int v, int l, int r, int L, int R) {
    push(v, l, r);
    if (L >= R) {
        return 0;
    }
    if (l == L && r == R) {
        return t[v];
    }
    int m = (l + r) / 2;
    int res = get(v * 2, l, m, L, min(m, R)) + get(v * 2 + 1, m, r, max(m, L), R);
    t[v] = t[v * 2] + t[v * 2 + 1];
    return res;
}

int32_t main() {
    cin >> n >> m;

    a = vector<int>(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    a.push_back(1e12);

    q = vector<pair<int, int>> (m);
    for (int i = 0; i < m; i++) {
        cin >> q[i].first >> q[i].second;
        --q[i].first;
    }

    vector<vector<int>> ev(n);
    for (int i = 0; i < m; i++) {
        ev[q[i].first].push_back(i);
    }

    vector<int> preSum(n + 1);
    for (int i = 0; i < n; i++) {
        preSum[i + 1] = preSum[i] + a[i];
    }

    vector<int> ans(m);
    for (int i = 0; i < m; i++) {
        ans[i] = -preSum[q[i].second] + preSum[q[i].first];
    }

    vector<int> st(1, n);
    t.assign(4 * n, 0);
    ps.assign(4 * n, 0);
    for (int i = n - 1; i >= 0; --i)
    {
        while (a[st.back()] <= a[i])
        {
            upd(1, 0, n, st.back(), st[st.size() - 2], -a[st.back()]);
            st.pop_back();
        }
        st.push_back(i);
        upd(1, 0, n, st.back(), st[st.size() - 2], a[st.back()]);
        for (int j : ev[i])
        {
            ans[j] += get(1, 0, n, q[j].first, q[j].second);
        }
    }
    for (int i = 0; i < m; i++) {
        cout << ans[i] << '\n';
    }
    return 0;
}
