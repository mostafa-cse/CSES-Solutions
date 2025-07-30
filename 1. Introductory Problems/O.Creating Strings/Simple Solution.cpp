#include <bits/stdc++.h>
#define int long long
using namespace std;
vector<int> fact(10);
signed main() {
    fact[0] = 1;
    for (int i = 1; i < 10; i++) {
        fact[i] = i * fact[i - 1];
    }
    string s;
    cin >> s;

    int n = s.size();
    int ans = fact[n];
    for (char c = 'a'; c <= 'z'; c++) {
        ans /= fact[count(s.begin(), s.end(), c)];
    }
    cout << ans << endl;
    
    sort(s.begin(), s.end());
    do {
        cout << s << endl;
    } while (next_permutation(s.begin(), s.end()));
    return 0;
}