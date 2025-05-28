#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    if (n * (n + 1) % 4) {
        return cout << "NO", 0;
    } 

    cout << "YES" << endl;
    map<int, bool> mark;
    int last = n;
    int sum = n * (n + 1) / 4;
    while (sum) {
        int mn = min(last, sum);
        sum -= mn;
        last--;
        mark[mn] = true;
    }
    
    int N = mark.size();
    
    cout << n - (int)mark.size() << endl;
    for (int i = 1; i <= n; i++) {
        // if (!mark[i]) cout << i << " "; // O(nlog)
        if (!mark.count(i)) cout << i << " "; // O(1)
    }

    cout << endl << mark.size() << endl;
    for (int i = 1; i <= n; i++) {
        // if (mark[i]) cout << i << " "; // O(nlog)
        if (mark.count(i)) cout << i << " "; // O(1)
    }
    return 0;
}