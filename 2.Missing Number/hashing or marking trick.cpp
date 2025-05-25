#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    map<int, bool> mark;
    for (int i = 1; i < n; i++) {
        int x;
        cin >> x;
        mark[x] = true;
    }

    for (int i = 1; i <= n; i++) {
        // if (!mark[i]) // log(n) complexity 
        if (mark.count(i) == 0) { // O(1) complexity
            return cout << i, 0;
        }
    }
    return 0;
}
