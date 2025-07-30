#include<bits/stdc++.h>
#define int long long
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);  cout.tie(0);
    int n, a, b;
    cin >> n >> a >> b;

    vector<int> ar(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
    	cin >> ar[i];
    	ar[i] += ar[i - 1];
    }

    multiset<int> st;
    for (int i = a; i <= b; i++) {
    	st.insert(ar[i]);
    }

    int ans = *st.rbegin();
    for (int i = 1; i + a <= n; ++i) {
    	st.erase(st.lower_bound(ar[i + a - 1]));
    	st.insert(ar[min(i + b, n)]);
    	ans = max(ans, *st.rbegin() - ar[i]);
    }
    cout << ans;
    return 0;
}
