#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    if (n % 4 == 1 || n % 4 == 2) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        vector<int> a, b;
        for (int i = n; i > 0; i = i - 4) {
            a.push_back(i);
            b.push_back(i - 1);
            b.push_back(i - 2);
            if (i - 3) {
                a.push_back(i - 3);
            }
        }

        cout << a.size() << endl;
        for (int i : a) {
            cout << i << " ";
        }

        cout << endl << b.size() << endl;
        for (int i : b) {
            cout << i << " ";
        }
    }
    return 0;
}