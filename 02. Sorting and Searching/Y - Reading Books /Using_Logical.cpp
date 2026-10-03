#include<bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()
int32_t main() {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);  cout.tie(0);
    int n;
    cin >> n;

    vector<int> a(n);
    for (int &i : a) {
        cin >> i;
    }
    sort(all(a));

    int sum = accumulate(all(a), 0LL) - a[n - 1];
    if (sum >= a[n - 1]) {
        cout << sum + a[n - 1];
    } else {
        cout << a[n - 1] * 2;
    }
    return 0;
}
