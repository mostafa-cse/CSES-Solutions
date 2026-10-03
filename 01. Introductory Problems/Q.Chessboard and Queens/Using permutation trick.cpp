#include <bits/stdc++.h>
using namespace std;
const int N = 8; 
int main() {
    vector<string> a(N);
    for (auto &u : a) {
        cin >> u;
    }
    vector<int> p = {0, 1, 2, 3, 4, 5, 6, 7};
    int ans = 0; 
    do { 
        bool ok = true;
        for (int i = 0; i < N and ok; i++) {
            if (a[i][p[i]] == '*') {
                ok = false;
            }
        }

        for (int i = 0; i < N and ok; i++) {
            for (int j = i + 1; j < N and ok; j++) {
                if (abs(p[i] - p[j]) == abs(i - j)) {
                    ok = false;
                }
            }
        }
        ans += ok; 
    } while(next_permutation(p.begin(), p.end())); 
    cout << ans;
    return 0;
}