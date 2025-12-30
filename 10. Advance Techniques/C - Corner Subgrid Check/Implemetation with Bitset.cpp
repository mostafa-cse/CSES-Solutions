#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()

const int M = 3000;
// Column-centric Bitset Optimization
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, k;
    cin >> n >> k;

    vector<string> a(n);
    for (string &i : a) {
        cin >> i;
    }
    for (char Ch = 'A'; Ch <'A' + k; Ch++) {
        vector<bitset<M>> store(n);
        bool ok = false;
        for (int i = 0; i < n and !ok; i++) {
            vector<int> pos;
            bitset<M> newVal;
            for (int j = 0; j < n; j++) {
                if (Ch == a[i][j]) {
                    pos.push_back(j);
                    newVal.set(j);
                }
            }
            // basecase = kom thakle jhamela create korbe
            if (pos.size() < 2) {
                continue;
            }

            for (int p : pos) {
                if ((store[p]&newVal).count() >= 2) {
                    ok = true;
                    break;
                }
                store[p] |= newVal;
            }
        }
        cout << (ok ? "YES" : "NO") << endl;
    }
    return 0;
}

