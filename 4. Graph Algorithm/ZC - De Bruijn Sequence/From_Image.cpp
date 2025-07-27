#include <bits/stdc++.h>
using namespace std;
const int N = 100003;
bool c[N], a[N];
int main() {
    int n;
    cin >> n;
    int mx = 1 << n, x = mx - 1;
    for (int i = 1; i <= n; i++) a[i] = 1;

    c[mx - 1] = 1;
    for (int i = n + 1; i <= mx; i++) {
        x %= mx / 2;
        if (!c[x * 2])
            c[x * 2] = 1, a[i] = 0, x = x * 2;
        else
            c[x * 2 + 1] = 1, a[i] = 1, x = x * 2 + 1;
    }
    for (int i = 1; i <= mx; i++)
        cout << a[i];
    for (int i = 1; i < n; i++)
        cout << "<";
    cout << endl;
    return 0;
}
