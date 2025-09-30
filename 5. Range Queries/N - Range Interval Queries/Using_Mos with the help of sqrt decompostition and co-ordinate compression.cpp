#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()

const int N = 2e5;
const int B = 265 + 5;
const int INF = 1e9 + 5;

int n;
int a[N];
int id[N];
int cnt[N];
int sum[B];
vector<int> t;

struct Query {
    int l, r, x, y, idx;
    bool operator<(const Query& other) const {
        int block_a = l / B, block_b = other.l / B;
        if (block_a != block_b) return block_a < block_b;
        return (block_a & 1) ? (r < other.r) : (r > other.r);
    }
};

void add(int x, int d) {
    cnt[x] += d;
    sum[id[x]] += d;
}

int get_answer(int l, int r) {
    int ans = 0;
    if (id[l] == id[r]) {
        for (int k = l; k <= r; k++) {
            ans += cnt[k];
        }
    } else {
        for (int k = l; k <= id[l] * B + B - 1; k++) {
            ans += cnt[k];
        }
        for (int k = id[r] * B; k <= r; k++) {
            ans += cnt[k];
        }
        for (int k = id[l] + 1; k < id[r]; k++) {
            ans += sum[k];
        }
    }
    return ans;
}

vector<int> mo_algorithm(vector<Query> Q) {
    vector<int> answers(Q.size());

    sort(Q.begin(), Q.end());
    int cur_l = 0, cur_r = -1;
    for (Query q : Q) {
        while (cur_l > q.l) {
            cur_l--;
            add(cur_l, 1);
        }
        while (cur_r < q.r) {
            cur_r++;
            add(cur_r, 1);
        }
        while (cur_l < q.l) {
            add(cur_l, -1);
            cur_l++;
        }
        while (cur_r > q.r) {
            add(cur_r, -1);
            cur_r--;
        }
        answers[q.idx] = get_answer(q.x, q.y);
    }
    return answers;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    for (int i = 0; i < N; i++) {
        id[i] = i / B;
    }

    int q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        t.push_back(a[i]);
    }

    sort(all(t));
    t.erase(unique(all(t)), t.end());

    vector<Query> Q;
    for (int i = 0; i < q; i++) {
        int l, r, x, y;
        cin >> l >> r >> x >> y;
        l--; r--;
        x = lower_bound(all(t), x) - t.begin();
        y = upper_bound(all(t), y) - t.begin();
        Q.push_back({l, r, x, y, i});
    }

    vector<int> ans = mo_algorithm(Q);
    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }
    return 0;
}
