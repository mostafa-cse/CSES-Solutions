#include <bits/stdc++.h>
using namespace std;
bool isV(int n, int y, int x) {
    return (y >= 0 && x >= 0 && y < n && x < n);
}
int calc (int n) {
    if (n == 1) return 0;
    if (n == 2) return 6;
    if (n == 3) return 28;
    int res = 0;
    for (int y = 0; y < 2; y++) {
        for (int x = 0; x < n - 2; x++) {
            int poss = n * n - 1;
            poss -= isV(n, x + 1, y + 2);
            poss -= isV(n, x - 1, y + 2);
            poss -= isV(n, x + 1, y - 2);
            poss -= isV(n, x - 1, y - 2);
            poss -= isV(n, x + 2, y + 1);
            poss -= isV(n, x + 2, y - 1);
            poss -= isV(n, x - 2, y + 1);
            poss -= isV(n, x - 2, y - 1);
            res += poss;
        }
    }
    res *= 4;
    res += (n - 4) * (n - 4) * (n * n - 9);
    return res / 2;
}
int main() {
    int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
        cout << calc(i) << endl;
    }
    return 0;
}