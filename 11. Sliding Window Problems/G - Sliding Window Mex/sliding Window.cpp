#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int &i : a) {
        cin >> i;
    }

    set<int> missing;
    map<int, int> cnt;
    function<void(int)> add = [&](int x) -> void {
        if (cnt[x] == 0) {
            missing.erase(x);
        }
        cnt[x]++;
    };
    function<void(int)> remove = [&](int x) -> void {
        cnt[x]--;
        if (cnt[x] == 0) {
            missing.insert(x);
        }
    };
    function<int(void)> MEX = [&]()-> int {
        return *missing.begin();
    };

    for (int i = 0; i <= k; i++) {
        missing.insert(i);
    }


    for (int i = 0; i < n; i++) {
        add(a[i]);
        if (i + 1 >= k) {
            cout << MEX() << " ";
            remove(a[i - k + 1]);
        }
    }
    return 0;
}

