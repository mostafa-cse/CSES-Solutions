#include<bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);  cout.tie(0);
    int n, k;
    cin >> n >> k;

    struct Range{
    	int start, end;
    	bool operator<(const Range &others){
    		return end < others.end;
    	}
    };

    vector<Range> a(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i].start >> a[i].end;
    }
    sort(all(a));

    int ans = 0;
	multiset<int> st;
	for (int i = 0; i < k; ++i) {
		st.insert(0);
	}

	for (auto el : a) {
		auto point = st.upper_bound(el.start);
		if (point != st.begin()) {
			ans++;
			st.erase(--point);
			st.insert(el.end);
		}
	}
	cout << ans;
    return 0;
}