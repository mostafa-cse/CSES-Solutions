#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef tree<pair<int, int>, null_type, less_equal<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> PBDS;
signed main() {
    int n;
    cin >> n;

    PBDS st;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        st.insert({i, x});
    }

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        auto Point = st.find_by_order(x - 1);
        cout << Point->second << " ";
        st.erase(Point);
    }
    return 0;
}