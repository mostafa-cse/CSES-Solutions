#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    if (n * (n + 1) % 4 != 0) {
        return cout << "NO", 0;
    }
    
    set<int> A, B;
    for (int i = 1; i <= n; i++) {
        A.insert(i);
    }
    
    int sum = n * (n + 1) / 4;
    for (int i = n; i >= 1; i--) {
        if (A.count(sum)) {
            B.insert(sum);
            A.erase(sum);
            break;
        }
        if (sum >= i) {
            B.insert(i);
            A.erase(i);
            sum -= i;
        }
    }

    cout << "YES" << endl;
    cout << A.size() << endl;
    for (int i : A) cout << i << " ";
    
    cout << endl << B.size() << endl;
    for (int i : B) cout << i << " ";
    return 0;
}