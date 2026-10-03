#include <bits/stdc++.h>
using namespace std;
#define len(v) (int)v.size()
#define all(x) x.begin(), x.end()
#define int long long

struct Block {
    int maks = 0;
    unordered_map<int, int> d;
    vector<int> arr, pref, suma, elems;
    Block(){}
    void build() {
        int k = len(arr);
        pref.assign(k + 1, 0);
        suma.assign(k + 1, 0);
        for (int i = 0; i < k; ++i) {
            if (arr[i] > maks) {
                elems.push_back(arr[i]);
                d[arr[i]] = i;
                maks = arr[i];
            }
            pref[i + 1] = pref[i] + maks - arr[i];
            suma[i + 1] = suma[i] + arr[i];
        }
    }
};
struct SQRT {
    vector<Block> bl;
    int k;
    SQRT(){}
    SQRT(vector<int>& a) {
        k = sqrtl(len(a)) * 4;
        int ind = -1;
        for (int i = 0; i < len(a); ++i) {
            if (ind != i / k) {
                ind++;
                bl.push_back(Block());
            }
            bl[ind].arr.push_back(a[i]);
        }

        for (auto& b : bl) {
            b.build();
        }
    }
    int ans(int l, int r) {
        int lb = l / k, rb = r / k, lind = l % k, rind = r % k;
        int ans = 0;
        int maks = 0;
        if (lb == rb) {
            for (int i = lind; i <= rind; ++i) {
                maks = max(maks, bl[lb].arr[i]);
                ans += maks - bl[lb].arr[i];
            }
            return ans;
        }
        if (lind != 0) {
            for (int i = lind; i < len(bl[lb].arr); ++i) {
                maks = max(maks, bl[lb].arr[i]);
                ans += maks - bl[lb].arr[i];
            }
            lb++;
        }
        for (int i = lb; i < rb; ++i) {
            if (maks >= bl[i].maks) {
                ans += maks * len(bl[i].arr) - bl[i].suma[len(bl[i].suma) - 1];
                continue;
            }
            int pind = upper_bound(all(bl[i].elems), maks) - bl[i].elems.begin();
            pind = bl[i].d[bl[i].elems[pind]];
            ans += maks * pind - bl[i].suma[pind];
            ans += bl[i].pref.back() - bl[i].pref[pind];
            maks = max(maks, bl[i].maks);

        }
        for (int i = 0; i <= rind; ++i) {
            maks = max(maks, bl[rb].arr[i]);
            ans += maks - bl[rb].arr[i];
        }
        return ans;
    }
};
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.precision(30);
    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    for (auto& c : a)cin >> c;

    SQRT s(a);
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        cout << s.ans(l, r) << "\n";
    }
    return 0;
}
