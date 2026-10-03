#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> PBDS;
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, k;
    cin >> n >> k;
    PBDS st;
    for (int i = 1; i <= n; i++) {
        st.insert(i);
    }

    int cur = 0;
    for (int i = 0; i < n; i++) {
        cur = (cur + k) % (n - i);
        auto val = st.find_by_order(cur);
        cout << *val << " ";
        st.erase(val);
    }
    return 0;
}
