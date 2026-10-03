#include<bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
#define int long long
using namespace std;
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> oset;
int32_t main() {
    int n, k;
    cin >> n >> k;

    vector<int> ar(n);
    for (int &i : ar) {
        cin >> i;
    }

    oset st;
    for (int i : ar) {
        st.insert(i);
    }

    while(k--) {
        char c;
        int a, b;
        cin >> c >> a >> b;

        if (c == '?') {
            int posA = st.order_of_key(a);
            int posB = st.order_of_key(b + 1);
            cout << posB - posA << endl;
        } else {
            st.erase(st.upper_bound(ar[a - 1]));
            st.insert(b);
            ar[a - 1] = b;
        }
    }
    return 0;
}