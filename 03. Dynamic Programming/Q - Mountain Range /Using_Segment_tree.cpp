#include <bits/stdc++.h>
using namespace std;
 
struct SegTree {
    int n;
    vector<int> st;
    SegTree(int _n): n(_n), st(4*n, 0) {}
    void update(int p, int val) { update(1, 0, n-1, p, val); }
    int query(int L, int R) { 
        if (L > R) return 0;
        return query(1, 0, n-1, L, R);
    }
private:
    void update(int node, int l, int r, int p, int val) {
        if (l == r) {
            st[node] = max(st[node], val);
            return;
        }
        int mid = (l + r) >> 1;
        if (p <= mid) update(node<<1, l, mid, p, val);
        else          update(node<<1|1, mid+1, r, p, val);
        st[node] = max(st[node << 1], st[node << 1 | 1]);
    }
    int query(int node, int l, int r, int L, int R) {
        if (r < L || R < l) return 0;
        if (L <= l && r <= R) return st[node];
        int mid = (l + r) >> 1;
        return max(query(node << 1, l, mid, L, R), query(node << 1 | 1, mid + 1, r, L, R));
    }
};
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n;
    cin >> n;
    vector<int> h(n);
    for (int i = 0; i < n; i++)
        cin >> h[i];
    vector<int> L(n), R(n);
    {
        stack<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && h[st.top()] < h[i])
                st.pop();
            L[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }
    }
    {
        stack<int> st;
        for (int i = n-1; i >= 0; i--) {
            while (!st.empty() && h[st.top()] < h[i])
                st.pop();
            R[i] = st.empty() ? n : st.top();
            st.push(i);
        }
    }
    vector<pair<int,int>> hs(n);
    for (int i = 0; i < n; i++)
        hs[i] = {h[i], i};
    sort(hs.begin(), hs.end());
    vector<int> dp(n, 0);
    SegTree seg(n);
 
    int answer = 1;
    for (int i = 0; i < n; ) {
        int j = i;
        while (j < n && hs[j].first == hs[i].first) j++;
        for (int k = i; k < j; k++) {
            int idx = hs[k].second;
            int left  = L[idx] + 1;
            int right = R[idx] - 1;
            int best = seg.query(left, right);
            dp[idx] = best + 1;
            answer = max(answer, dp[idx]);
        }
        for (int k = i; k < j; k++) {
            int idx = hs[k].second;
            seg.update(idx, dp[idx]);
        }
        i = j;
    }
    cout << answer << "\n";
    return 0;
}