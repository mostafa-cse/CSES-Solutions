#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update>

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int &i : a) {
        cin >> i;
    }

    ordered_set o_set;
    for (int i = 0; i < n; i++) {
        o_set.insert(a[i]);
        if (i + 1 >= k) {
            int median = *o_set.find_by_order((k - 1) >> 1);
            cout << median << " ";
            o_set.erase(o_set.upper_bound(a[i - k + 1]));
        }
    }
    return 0;
}
