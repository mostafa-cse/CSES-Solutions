#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> applicants(n);
    for (int &i : applicants) {
        cin >> i;
    }
    sort(applicants.rbegin(), applicants.rend());

    multiset<int> room;
    for (int i = 0; i < m; ++i) {
        int x; cin >> x;
        room.insert(x);
    }

    int ans = 0;
    for (int i = 0; i < n and !room.empty(); ++i) {
        auto pos = room.upper_bound(applicants[i] + k);
        if (pos != room.begin()) pos--;
        if (*pos <= applicants[i] + k and *pos >= applicants[i] - k) {
            ans++;
            room.erase(pos);
        }
    }
    cout << ans;
    return 0;
}