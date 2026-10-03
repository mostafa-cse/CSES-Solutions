#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    vector<int> a;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        auto it = upper_bound(a.begin(), a.end(), x) - a.begin();
        if (it == a.size()) a.push_back(x);
        else {
            a[it] = x;
        } 
    }
    cout << a.size();
    return 0;
}