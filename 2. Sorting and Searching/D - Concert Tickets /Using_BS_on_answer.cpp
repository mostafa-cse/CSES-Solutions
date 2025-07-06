#include <bits/stdc++.h>
using namespace std;

typedef long long L;

int main() {
    L n, m;
    cin >> n >> m;

    vector<L> a(n);
    for (L& x : a) {
        cin >> x;
    }

    sort(a.begin(), a.end());

    vector<L> st, num, ans_index;
    st.push_back(-1);
    num.push_back(0);
    ans_index.push_back(0);

    for (L i = 0; i < n; ++i) {
        if (i > 0 && a[i] == a[i - 1]) {
            num.back()++;
        } else {
            st.push_back(a[i]);
            num.push_back(1);
            ans_index.push_back(st.size() - 1);
        }
    }

    auto f1 = [&](L u) {
        L l = 0, r = st.size() - 1, anss = 0;
        while (l <= r) {
            L mid = (l + r) / 2;
            if (u < st[mid]) {
                r = mid - 1;
            } else {
                l = mid + 1;
                anss = mid;
            }
        }
        return anss;
    };

    function<int(int)> f2 = [&](L u) {
        return (ans_index[u] != u) ? (ans_index[u] = f2(ans_index[u])) : u;
    };

    while (m--) {
        L b;
        cin >> b;
        L c = f1(b), d = f2(c);
        if (num[d] > 0) {
            cout << st[d] << '\n';
            if (--num[d] == 0) {
                ans_index[d] = ans_index[d - 1];
            }
        } else {
            cout << -1 << '\n';
        }
    }
    return 0;
}
