#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> app(n), room(m);
    for (int &i : app) cin >> i;
    for (int &i : room) cin >> i;

    sort(app.begin(), app.end(), greater<>());
    sort(room.begin(), room.end(), greater<>());

    int i = 0, j = 0, ans = 0;
    while (i < n and j < m) {
        if (app[i] >= room[j] - k and app[i] <= room[j] + k) {
            ans++;
            j++;
            i++;
        } else {
            if (app[i] > room[j] + k) {
                i++;
            } else if (app[i] < room[j] - k) {
                j++;
            }
        }
    }
    cout << ans << endl;
    return 0;
}