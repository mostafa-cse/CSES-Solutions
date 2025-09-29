#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
#define int long long
using namespace std;
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> PBDS;
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
struct Query {
    int l, r, a, b, idx, ord;
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
    int curL = 0, curR = -1;
    int rA = 0, rB = 0;
    virtual void add(int pos) = 0;
    virtual void remove(int pos) = 0;
    virtual int getAnswer(int, int) = 0;
public:
    vector<Query> qs;
    MoBase(vector<int> arr): n((int)arr.size()), a(arr) {}
    void addQuery(int l, int r, int a, int b,int idx) {
        qs.push_back({l, r, a, b, idx, Query::gilbertOrder(l, r)});
    }
    vector<int> process(int qcount) {
        sort(qs.begin(), qs.end(), [](const Query& A, const Query& B){ return A.ord < B.ord; });
        vector<int> ans(qcount);
        for (const auto &Q : qs) {
            while (curL > Q.l) add(--curL);
            while (curR < Q.r) add(++curR);
            while (curL < Q.l) remove(curL++);
            while (curR > Q.r) remove(curR--);
            ans[Q.idx] = getAnswer(Q.a, Q.b);
        }
        return ans;
    }
};
struct MoDistinct : MoBase {
    int ans = 0;
    PBDS st;
    int N;
    MoDistinct(const vector<int> &arr) : MoBase(arr), N(arr.size()) {}
    void add(int pos) override {
        int val = a[pos];
        st.insert(val);
    }
    void remove(int pos) override {
        int val = a[pos];
        auto el = st.upper_bound(val);
        st.erase(el);
    }
    int getAnswer(int a, int b) override {
        int R = st.order_of_key(b + 1);
        int L = st.order_of_key(a);
        return R - L;
    }
};
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(NULL);

    int n, q;
    cin >> n >> q;

    vector<int> v(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }

    MoDistinct Mos(v);
    for (int i = 0; i < q; i++) {
        int l, r, a, b;
        cin >> l >> r >> a >> b;
        Mos.addQuery(l, r, a, b, i);
    }
    vector<int> ans = Mos.process(q);
    for (int i : ans) {
        cout << i << "\n";
    }
    return 0;
}
