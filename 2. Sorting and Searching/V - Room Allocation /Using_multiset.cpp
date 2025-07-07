#include <bits/stdc++.h>
#define SPED ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define endl "\n"
#define lint long long
const lint INF = 1e15;
using namespace std;

struct people {
    lint fi, se, idx;
};

int n, ans[200005];
people a[200005];
lint nowroom;
multiset<pair<lint, lint>, greater<pair<lint, lint>>> hotel;

bool cmp(people x, people y) {
    return x.se < y.se;
}

int main() {
    SPED;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].fi >> a[i].se;
        a[i].idx = i;
    }
    sort(a + 1, a + 1 + n, cmp);
    for (int i = 1; i <= n; i++) {
        auto room = hotel.upper_bound({a[i].fi, -INF});
        if (room == hotel.end()) {
            nowroom = hotel.size() + 1;
            hotel.insert({a[i].se, nowroom});
        } else {
            nowroom = (*room).second;
            hotel.erase(room);
            hotel.insert({a[i].se, nowroom});
        }
        ans[a[i].idx] = nowroom;
    }
    cout << hotel.size() << endl;
    for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
    cout << endl;
    return 0;
}
