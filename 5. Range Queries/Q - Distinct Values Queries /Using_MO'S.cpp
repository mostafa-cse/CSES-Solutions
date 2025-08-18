#include <bits/stdc++.h>
#define int long long
using namespace std;
struct Query {
    int l, r, idx;
    int ord;
    static int gilbertOrder(int x, int y, int pow = 21, int rotate = 0) {
        if (pow == 0) return 0;
        int h = 1 << (pow - 1);
        int seg = (x < h) ? ((y < h) ? 0 : 3) : ((y < h) ? 1 : 2);
        seg = (seg + rotate) & 3;
        const int rotateDelta[4] = {3, 0, 0, 1};
        int nx = x & (h - 1);
        int ny = y & (h - 1);
        int nrot = (rotate + rotateDelta[seg]) & 3;
        int subSquareSize = 1LL << (2 * pow - 2);
        int ord = seg * subSquareSize;
        int add = gilbertOrder(nx, ny, pow - 1, nrot);
        return ord + ((seg == 1 || seg == 2) ? add : (subSquareSize - add - 1));
    }
};
struct MoBase {
protected:
    int n;
    vector<int> a;
    vector<Query> qs;
    int curL = 0, curR = -1;
    virtual void add(int pos) = 0;
    virtual void remove(int pos) = 0;
    virtual int getAnswer() = 0;
public:
    MoBase(const vector<int>& arr): n((int)arr.size()), a(arr) {}
    void addQuery(int l, int r, int idx) {
        qs.push_back({l, r, idx, Query::gilbertOrder(l, r)});
    }
    vector<int> process(int qcount) {
        sort(qs.begin(), qs.end(), [](const Query& A, const Query& B){ return A.ord < B.ord; });
        vector<int> ans(qcount);
        for (const auto &Q : qs) {
            while (curL > Q.l) add(--curL);
            while (curR < Q.r) add(++curR);
            while (curL < Q.l) remove(curL++);
            while (curR > Q.r) remove(curR--);
            ans[Q.idx] = getAnswer();
        }
        return ans;
    }
};
struct moOperate : MoBase {
    int ans = 0;
    vector<int> cnt;
    moOperate(const vector<int> &arr, int alphabet_size) : MoBase(arr) {
        cnt.resize(alphabet_size + 1, 0);
    }
    void add(int pos) override {
        int val = a[pos];
        ans += !cnt[val];
        cnt[val]++;
    }
    void remove(int pos) override {
        int val = a[pos];
        cnt[val]--;
        ans -= !cnt[val];
    }
    int getAnswer() override {
        return ans;
    }
};
signed main() {
    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> b = a;
    sort(b.begin(), b.end());
    b.resize(unique(b.begin(), b.end()) - b.begin());
    for (int i = 0; i < n; i++) {
        a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
    }

    moOperate mos(a, b.size());
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        mos.addQuery(l - 1, r - 1, i);
    }

    for (int i : mos.process(q)) {
        cout << i << "\n";
    }
    return 0;
}