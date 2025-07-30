#include <bits/stdc++.h>
using namespace std;

int main () {
    int n;
    cin >> n;
    for(int k = 1; k <= n; k++) {
        long double tot = 0;
        int h = k * k;
        tot = (h) * ((h - 1) / 2.0);
        tot -= ((k - 2) * 10) + (4) + ((k - 4) * (k - 2) * 4) + ((k - 4) * 2);
        cout << fixed << (long long) tot << "\n";
    }
    return 0;
}