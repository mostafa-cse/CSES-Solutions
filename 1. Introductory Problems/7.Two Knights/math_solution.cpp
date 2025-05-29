#include<bits/stdc++.h>
#define int long long
using namespace std;

int32_t main() {
    int n;
    cin >> n;
 
    for (int i = 1; i <= n; ++i) {
        int total = pow(i, 2) * (pow(i, 2) - 1) / 2;
        int attacking = 4 * (i - 1) * (i - 2);
 
        cout << total - attacking << endl;
    }
    return 0;
}