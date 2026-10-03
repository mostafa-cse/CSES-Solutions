#include<bits/stdc++.h>
#define int long long
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);  cout.tie(0);
    int n, a, b;
    cin >> n >> a >> b;

    vector<int> ar(n + 1, 0);
    for (int i = 1; i <= n; i++) {
    	cin >> ar[i];
		ar[i] += ar[i - 1];
    }
    multiset<int> st;
    int ans = -1e18;
    for (int i = a; i <= n; i++) {
    	if (i > b) {
    	    st.erase(st.find(ar[i - b - 1]));
    	}
    	st.insert(ar[i - a]);
    	ans = max(ans, ar[i] - *st.begin());
    }
    cout << ans;
    return 0;
}
