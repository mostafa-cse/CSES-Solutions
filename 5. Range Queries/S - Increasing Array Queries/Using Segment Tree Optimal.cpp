#include <bits/stdc++.h>
#define int long long
#define N 300005
using namespace std;

int n;
int a[N], mn[N * 3], mx[N * 3];
int s[N * 3], sum[N * 3];
void build(int node, int l, int r) {
    if (l == r) {
        mn[node] = mx[node] = a[l];
        s[node] = 0;
        sum[node] = a[l];
        return;
    }
    build(node * 2, l, (l + r) / 2);
    build(node * 2 + 1, (l + r) / 2 + 1, r);

    // merge two sides
    mn[node] = a[l];
    mx[node] = a[l];
    sum[node] = a[l];
    s[node] = 0;
    for (int i = l + 1; i <= r; i++) {
        if (a[i] > mx[node]) {
            mx[node] = a[i];
            sum[node] += a[i];
        } else {
            s[node] += mx[node] - a[i];
            sum[node] += mx[node];
        }
    }
    return;
}

int nowMX, ans;
void query(int node, int l, int r, int b, int e) {
    if (r < b || e < l) {
        return;
    }
    if (b <= l && r <= e) {
        if (mn[node] >= nowMX) {
            ans += s[node];
            nowMX = mx[node];
            return;
        } else if (mx[node] <= nowMX) {
            ans += (r - l + 1) * nowMX - sum[node];
            ans += s[node];
            return;
        } else {
            query(node * 2, l, (l + r) / 2, b, e);
            query(node * 2 + 1, (l + r) / 2 + 1, r, b, e);
            return;
        }
    }
    query(node * 2, l, (l + r) / 2, b, e);
    query(node * 2 + 1, (l + r) / 2 + 1, r, b, e);
    return;
}

main() {
    int q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    build(1, 1, n);

    while (q--) {
        nowMX = ans = 0;
        int l, r;
        cin >> l >> r;

        query(1, 1, n, l, r);
        cout << ans << '\n';
    }
    return 0;
}
