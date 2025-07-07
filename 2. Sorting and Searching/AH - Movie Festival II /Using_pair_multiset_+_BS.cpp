#include <bits/stdc++.h>
using namespace std;

const int N = (int)2e5 + 7;
int n, k;
pair<int, int> p[N];

bool cmp(pair<int, int> a, pair<int, int> b) {
    return a.second < b.second;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> p[i].first >> p[i].second;
    }
    sort(p + 1, p + 1 + n, cmp);  
    
    multiset<int> s;
    for (int i = 1; i <= k; ++i) {
        s.insert(0);
    }
    
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        auto it = s.upper_bound(p[i].first);
        if (it != s.begin()) {
            it--;
            s.erase(it);
            s.insert(p[i].second);
            ans++;
        }
    }
    cout << ans;
    return 0;
}