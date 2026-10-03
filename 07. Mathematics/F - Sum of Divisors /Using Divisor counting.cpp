#include <bits/stdc++.h>
using namespace std;
#define int long long
const int M = 1000000007;
const int INV2 = 500000004;

int sum(int a, int b) {
    return (a + b) % M * ((b - a + 1) % M) % M * INV2 % M;
}

int main() {
    int n;
    cin >> n;

    int s = 0;
    for (int k = 1; k * k <= n; k++) {
        s += (n / k) * k;
        s %= M;
    }
    cout << endl;

    for (int k = 1; n / k > k; k++) {
        s += sum(n / (k + 1) + 1, n / k) * k;
        s %= M;
    }
    cout << s << "\n";
}
