#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, a[200005], q[1<<20];
vector<int> ans;

void fwht(int val[], int sz, bool inv = false) { // 
    for (int len = 2; len <= sz; len <<= 1) {
        for (int i = 0; i < sz; i += len) {
            for (int j = i; j < i + len / 2; j++) {
                int x = val[j], y = val[j + len / 2];
                val[j] = x + y;
                val[j + len / 2] = x - y;
            }
        }
    }

    if (inv) {
        for (int i = 0; i < sz; i++) {
            val[i] /= sz;
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n;

    q[0]++;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] ^= a[i - 1];
        q[a[i]]++;
    }


    for (int i = 0; i < (1 << 20); i++) {
        if (q[i] >= 2) {
            ans.push_back(0);
            break;
        }
    }

    fwht(q, 1 << 20);
    for (int i = 0; i < (1 << 20); i++) {
        q[i] = q[i] * q[i];
    }

    fwht(q, 1 << 20, true);
    for (int i = 1; i < (1 << 20); i++) {
        if (q[i]) {
            ans.push_back(i);
        }
    }

    cout << ans.size() << '\n';
    for (int i : ans) {
        cout << i << ' ';
    }
    return 0;
}
