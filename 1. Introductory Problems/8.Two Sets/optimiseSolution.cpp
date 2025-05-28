#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n = 0;
    cin >> n;
    int sum = 0;
    sum = n * (n + 1) / 2;
    if (sum % 2 != 0) {
        cout << "NO" << endl;
        return;
    }

    cout << "YES" << endl;
    vector<int> set1, set2;
    int half = sum / 2;
    for (int i = n; i >= 1; --i) {
        if (half - i >= 0) {
            set1.push_back(i);
            half -= i;
        } else {
            set2.push_back(i);
        }
    }

    cout << set1.size() << endl;
    for (int num : set1)
        cout << num << " ";

    cout << endl << set2.size() << endl;
    for (int num : set2)
        cout << num << " ";
    cout << endl;
    return 0;
}