#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int N = (int)2e5 + 9, inf = 1e9 + 9;

vector<int> v;
// array values can be negative too, use appropriate minimum and maximum value
#define pii pair<int,int>
#define x first
#define y second
int n = N;
struct wavelet_tree {
    static const int unfound = INT_MIN;
    static const int maxn = 2e5 + 5;
    static const int mlog = 20;
    typedef int Int;
    typedef long long Long;
    Int s[maxn], tree[mlog][maxn];
    int l[mlog][maxn];
    Long ls[mlog][maxn], sl;

    Int & operator[](int x) {return tree[0][x];}

    void build(Int l = 1, int r = n, int d = 0) {
        if (l == r) return;
        int m = l + r >> 1, cnt = 0, lc = l, rc = m + 1, ec = 0;
        for (int i = l; i <= r; i++) if (tree[d][i] <= s[m]) cnt++;
        for (int i = l; i <= r; i++) {
            if ((tree[d][i] < s[m]) || (tree[d][i] == s[m] && ec < (m - l + 1 - cnt))) {
                tree[d + 1][lc++] = tree[d][i];
                ls[d + 1][i] = ls[d + 1][i - 1] + tree[d][i];
                if (tree[d][i] == s[m]) ec++;
            } else {
                tree[d + 1][rc++] = tree[d][i];
                ls[d + 1][i] = ls[d + 1][i - 1] + tree[d][i];
            }
            ls[d][i] = ls[d][i - 1] + lc - l;
        }
        build(l, m, d + 1); build(m + 1, r, d + 1);
    }

    void init(Int *arr, int n_) {
        n = n_;
        for (int i = 1; i <= n; i++) tree[0][i] = arr[i];
        init(n);
    }

    void init(int n) {
        for (int i = 1; i <= n; i++) s[i] = tree[0][i], ls[0][i] = ls[0][i - 1] + s[i];
        sort(s + 1, s + n);
        build();
    }

    Long sum(pii a, int d = 0) {return ls[d][a.y] - ls[d][a.x - 1];}
    int cn(pii a, int d) {return l[d][a.y] - l[d][a.x - 1];}
    pii left(pii a, int d, int l) {return {l + cn({l, a.x - 1}, d), l + cn(a, d)};}
    pii right(pii a, int d, int r) {return {a.x + cn(a.x, r, d), a.y + cn(a.y + 1, r, d)};}

    Long leqsum(int x, int y, Int k, int l = 1, int r = n, int d = 0) {
        if (l == r) {
            if (l > y || l < x) return 0;
            return tree[d][l] * (tree[d][l] <= k);
        }
        int cnt = cn({x, y}, d), m = l + r >> 1, nx, ny;
        if (s[m] <= k) {
            tie(nx, ny) = right({x, y}, d, r);
            return sum({x, y}, d + 1) + leqsum(nx, ny, k, m + 1, r, d + 1);
        } else {
            tie(nx, ny) = left({x, y}, d, l);
            return leqsum(nx, ny, k, l, m, d + 1);
        }
    }
} t;

int a[N];
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int q; cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 1; i <= n; i++) t[i] = a[i];

    t.init(n);
    while (q--) {
        int l, r; cin >> l >> r;
        ll tot_sum = t.leqsum(l, r, inf);
        ll sum = 0;
        int op = 0;
        while (1) {
            if (sum == tot_sum) {
                cout << sum + 1 << '\n';
                break;
            }
            ll x = t.leqsum(l, r, min((ll)inf, sum + 1));
            if (x > sum) sum = x;
            else {
                cout << sum + 1 << '\n';
                break;
            }
            ++op;
            assert(op <= 50);
        }
    }
    return 0;
}
