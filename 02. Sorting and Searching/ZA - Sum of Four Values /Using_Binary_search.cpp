#include<bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()

int32_t main() {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);  cout.tie(0);
    int n, k;
    cin >> n >> k;

    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }

    map<int, vector<pair<int, int>>> Sum;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i].first + a[j].first < k) {
                Sum[a[i].first + a[j].first].push_back({a[i].second, a[j].second});
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; j++) {
            int rem = k - a[i].first - a[j].first;
            if (!Sum[rem].empty()) {
                for (auto p : Sum[rem]) {
                    set<int> s = {p.first, p.second, i, j};
                    if (s.size() == 4) {
                        return cout << i + 1 << " " << j + 1 << " " << p.first + 1 << " " << p.second + 1, 0;
                    }
                }
            }
        }
    }
    cout << "IMPOSSIBLE";
    return 0;
}
