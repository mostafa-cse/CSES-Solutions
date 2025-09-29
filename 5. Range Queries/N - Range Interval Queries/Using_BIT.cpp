#include <bits/stdc++.h>
using namespace std;

const int N = 203000;
const int B = 450;

int a[N];
int cnt[N];
int pos[N];

template <typename T>
inline T read() {
    T f = 1;
    T x = 0;
    int ch = getchar();
    while (ch != EOF && !isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch != EOF && isdigit(ch)) {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

inline void solve() {
    int n = read<int>();
    int q = read<int>();

    vector<int> lsh;
    lsh.reserve(n);
    for (int i = 1; i <= n; ++i) {
        a[i] = read<int>();
        lsh.push_back(a[i]);
    }

    sort(lsh.begin(), lsh.end());
    lsh.erase(unique(lsh.begin(), lsh.end()), lsh.end());
    int M = (int)lsh.size();

    for (int i = 1; i <= n; ++i) {
        a[i] = int(lower_bound(lsh.begin(), lsh.end(), a[i]) - lsh.begin()) + 1;
    }

    int blk_cnt = (M + B - 1) / B;
    if (blk_cnt == 0) blk_cnt = 1;

    vector<int> L(blk_cnt + 2), R(blk_cnt + 2), sum(blk_cnt + 2, 0);
    for (int i = 1; i <= blk_cnt; ++i) {
        L[i] = (i - 1) * B + 1;
        R[i] = min(i * B, M);
        for (int j = L[i]; j <= R[i]; ++j) pos[j] = i;
    }

    struct Query { int l, r, x, y, idx; };
    vector<Query> qu(q);
    for (int i = 0; i < q; ++i) {
        int l = read<int>();
        int r = read<int>();
        int x = read<int>();
        int y = read<int>();

        int dx = int(lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin()) + 1;
        int dy = int(upper_bound(lsh.begin(), lsh.end(), y) - lsh.begin());
        dx = max(dx, 1);
        dy = min(dy, M);

        qu[i] = {l, r, dx, dy, i};
    }

    sort(qu.begin(), qu.end(), [&](const Query &A, const Query &Bq) {
        int ablock = A.l / B;
        int bblock = Bq.l / B;
        if (ablock == bblock) {
            if (ablock % 2 == 0) return A.r < Bq.r;
            else return A.r > Bq.r;
        }
        return A.l < Bq.l;
    });

    auto add = [&](int idx) {
        int val = a[idx];
        ++cnt[val];
        ++sum[pos[val]];
    };

    auto del = [&](int idx) {
        int val = a[idx];
        --cnt[val];
        --sum[pos[val]];
    };

    auto findans = [&](int lval, int rval) -> int {
        if (lval > rval) return 0;
        int ans = 0;
        int p = pos[lval];
        int qpos = pos[rval];
        if (p == qpos) {
            for (int i = lval; i <= rval; ++i) ans += cnt[i];
            return ans;
        }
        for (int b = p + 1; b <= qpos - 1; ++b) ans += sum[b];
        for (int i = lval; i <= R[p]; ++i) ans += cnt[i];
        for (int i = L[qpos]; i <= rval; ++i) ans += cnt[i];
        return ans;
    };

    vector<int> res(q);
    int cl = 1, cr = 0;

    for (auto &Q : qu) {
        int Lq = Q.l, Rq = Q.r;
        while (cl > Lq) add(--cl);
        while (cr < Rq) add(++cr);
        while (cl < Lq) del(cl++);
        while (cr > Rq) del(cr--);
        res[Q.idx] = findans(Q.x, Q.y);
    }

    for (int i = 0; i < q; ++i) {
        cout << res[i] << '\n';
    }
}

int main() {
    solve();
    return 0;
}
