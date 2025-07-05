#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    set<int> s;
    for (int i = 1; i <= n; i++) {
        s.insert(i);
    }

    int flag = false;
    int cnt = 1;
    while (s.size() > 1) {
        set<int> q;
        for (auto i : s) {
            if (~cnt & 1) q.insert(i), cout << i << " ";
            cnt++;
        }
        for (auto i : q) {
            s.erase(i);
        }
    }
    cout << *s.begin() << endl;
    return 0;
}