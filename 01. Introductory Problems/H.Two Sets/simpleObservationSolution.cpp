#include <bits/stdc++.h>
#define int long long
using namespace std;

int32_t main() {
    int n;
    cin >> n;
    
    if ((n * (n + 1) / 2) & 1) {
        cout << "NO" << '\n';
        return 0;
    }

    vector<int> s1, s2;
    if (n & 1) {
        int sum = (n * (n + 1) / 4);
        for (int i = n; i >= 1; --i) {
            if (i > sum) {
                s2.push_back(i);
            } else {
                sum -= i;
                s1.push_back(i);
            }
        }
    } else {
        int x = n / 2;
        for (int i = 1; i <= x; i++) {
            if (i & 1) {
                s1.push_back(i);
                s1.push_back(n + 1 - i);
            } else {
                s2.push_back(i);
                s2.push_back(n + 1 - i);
            }
        }
    }

    cout << "YES" << '\n';
    cout << s1.size() << endl;
    for (int i = 0; i < s1.size(); i++) {
        cout << s1[i] << " ";
    }

    cout << endl << s2.size() << endl;
    for (int i = 0; i < s2.size(); i++) {
        cout << s2[i] << " ";
    }
    return 0;
}