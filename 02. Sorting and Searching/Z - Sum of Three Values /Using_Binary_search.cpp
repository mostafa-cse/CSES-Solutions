#include<bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()
bool check(pair<int, int> a, pair<int, int> &b) {
    return (a.second != b.second);
}
int32_t main() {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);  cout.tie(0);
    int n, k;
    cin >> n >> k;

    vector<pair<int, int>> a(n);
    multiset<pair<int, int>> st;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i + 1;
        st.insert(a[i]);
    }
    sort(all(a));

    for(int i = 0; i < n; i++) {
        pair first = a[i];
        for (int j = i + 1; j < n; j++) {
            pair second = a[j];
            int rem = k - first.first - second.first;
            auto it = st.lower_bound({rem, -1});
            if (it != st.end() and check((*it), first) and check((*it), second)) {
                if ((*it).first == rem) {
                    return cout << first.second << " " << second.second << " " << (*it).second, 0;
                }
            }
        }
    }
    cout << "IMPOSSIBLE";
    return 0;
}
