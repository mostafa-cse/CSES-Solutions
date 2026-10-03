#include<bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
#define int long long
using namespace std;
typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> PBDS;
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);  cout.tie(0);
    int n;
    cin >> n;
 
    vector<int> a(n);
    PBDS st;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        st.insert({a[i], i});
    }
 
    int ans = 0;
    for (int i = 0; i < n; i++) {
        auto el = st.lower_bound({a[i], i});
        
        if (el == st.end()) continue;
        
        ans += (el->first == a[i]);
        
        int prev = a[i] + 1, previ = i;
        while (true) {
            auto point = st.lower_bound({prev, previ});
            if (prev != point->first or point->second < previ) {
                break;
            }
            prev = point->first, previ = point->second;
            st.erase(point);
        }
        cout << endl;
    }
    cout << ans;
    return 0;
}