#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;

    set<long long> pick;

    long long total = (long long)(n * (n + 1));
    total = total / 2;
    if (total % 2) {
        cout << "NO" << endl;
    } else {
        long long target = total / 2;
        long long largest = n;
        while (target >= 0 && target >= largest) {
            pick.insert(largest);
            target -= largest;
            largest--;
        }
        if (target != 0) pick.insert(target);

        cout << "YES" << endl;
        cout << pick.size() << endl;
        for (auto it : pick) {
            cout << it << " ";
        }

        cout << endl << n - pick.size() << endl;
        for (int i = 1; i <= n; i++){
            if (!pick.count(i)) {
                cout << i << " ";
            }
        }
        cout << endl;
    }
    return 0;
}