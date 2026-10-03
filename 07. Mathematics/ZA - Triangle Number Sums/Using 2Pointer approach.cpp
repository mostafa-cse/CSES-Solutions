#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAX = 1e12 + 1;
vector<int> traingle;
void solve() {
    int x;
    cin >> x;
    if (binary_search(traingle.begin(), traingle.end(), x)) {
        cout << 1 << endl;
    } else {
        int l = 0, r = traingle.size() - 1;
        while (l <= r) {
            int sum = traingle[l] + traingle[r];
            if (sum == x) {
                cout << 2 << endl;
                return;
            } else if (sum > x) {
                r--;
            } else {
                l++;
            }
        }
        cout << 3 << endl;
    }
}
signed main() {
    for (int i = 1, sum = 0; sum < MAX; i++) {
        sum += i;
        traingle.push_back(sum);
    }
    int tc;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case " << t << ": ";
        solve();
    }
    return 0;
}
