#include <bits/stdc++.h>
using namespace std;

signed main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    nth_element(a.begin(), a.begin() + (n >> 1), a.end());

    cout << accumulate(a.begin(), a.end(), 0LL, [&](long long Sum, int v) { 
        return Sum + abs(v - a[n / 2]); 
    }) << endl;
    return 0;
}