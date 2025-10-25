#include <bits/stdc++.h>
#define int long long
using namespace std;

int count(int x) {
    int c = 0;
    for (int k = 1; k * k <= x; k++) {
        if (x % k) continue;
        c++;
        if (k != x / k) c++;
    }
    return c;
}
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cout << count(x) << "\n";
    }
}
