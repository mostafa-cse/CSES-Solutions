#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
#define int long long
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> PBDS;

const int M = 21;
int fact[M];
void factorial() {
    fact[0] = 1;
    for (int i = 1; i <= 20; ++i) {
        fact[i] = fact[i - 1] * i;
    }
}
signed main() {
    factorial();
    int tc;
    cin >> tc;

    while (tc--) {
        int t, n;
        cin >> t >> n;

        PBDS permutation;
        for (int i = 1; i <= n; i++) {
            permutation.insert(i);
        }

        if (t == 1) {
            int k;
            cin >> k;

            for (int i = n; i >= 1; i--) {
                int nominator = k - 1;
                int denominator = fact[i - 1];

                int pos = nominator / denominator;
                auto value = permutation.find_by_order(pos);

                cout << *value << " ";

                permutation.erase(value);
                k = (nominator % denominator) + 1; // aita 1-based koresi
            }
            cout << endl;
        } else {
            int k = 1;
            for (int i = n; i >= 1; i--) {
                int x;
                cin >> x;

                auto val = permutation.order_of_key(x);
                k += val * fact[i - 1];

                permutation.erase(permutation.find_by_order(val));
            }
            cout << k << endl;
        }
    }
    return 0;
}
