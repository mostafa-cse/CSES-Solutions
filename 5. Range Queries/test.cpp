#include <bits/stdc++.h>
#define int long long
using namespace std;
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
signed main() {
    int n;
    cin >> n;
    cout << bitset<10>(n) << endl;
    cout << bitset<10>(-n) << endl;
    cout << bitset<10>(n & -n) << endl;
    return 0;
}