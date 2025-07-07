#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    queue<int> q;
    for (int i = 1; i <= n; i++) {
        q.push(i);
    }

    int flag = false;
    while (!q.empty()) {
        int val = q.front();
        q.pop(); 
        
        if (flag) {
            cout << val << " ";
        } else {
            q.push(val);
        }
        flag ^= true;
    }
    return 0;
}