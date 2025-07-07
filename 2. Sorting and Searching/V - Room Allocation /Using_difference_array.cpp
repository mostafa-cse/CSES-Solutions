#include<bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;

    vector<pair<int, pair<int, int>>> v;
    for (int i = 1, x, y; i <= n; i++) {
        cin >> x >> y;
        v.push_back({x, {-1, i}}); // comes in
        v.push_back({y, {1, i}});  // goes out
    }
    sort(v.begin(), v.end());

    vector<int> rooms;
    int occupied = 0, max_rooms = 0;
    int ans[n + 1];
    for (auto ele : v) {
        int in_or_out = ele.second.first;
        int ind = ele.second.second;

        if (in_or_out == 1) {
            // going out, so add that room number to rooms
            rooms.push_back(ans[ind]);
        } else if (occupied == rooms.size()) {
            // no more vacant rooms, so increase number of rooms
            ans[ind] = ++max_rooms;
        } else {
            // give a room and increase occupancy count
            ans[ind] = rooms[occupied++];
        }
    }

    cout << max_rooms << endl;
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}
