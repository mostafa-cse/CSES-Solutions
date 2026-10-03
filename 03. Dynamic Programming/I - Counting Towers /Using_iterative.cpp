#include <bits/stdc++.h>
using namespace std;
#define int long long
 
const int mod = 1e9 + 7;
const int N = 1e6 + 10;
int one[N], two[N];

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    one[1] = two[1] = 1;
    for (int i = 2; i < N; i++) {
        one[i] = (2 * one[i - 1] + two[i - 1]) % mod;
        two[i] = (4 * two[i - 1] + one[i - 1]) % mod;
    }
 
    int t;
    cin >> t;
    while (t--){
        int n; cin >> n;
        cout << (one[n] + two[n]) % mod << "\n";
    }       
    return 0;
}