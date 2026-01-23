#include <bits/stdc++.h>
using namespace std;
struct CoordCompressor {
    vector<int> coords;
    void add(int x) { coords.push_back(x); }
    void build() {
        sort(coords.begin(), coords.end());
        coords.erase(unique(coords.begin(), coords.end()), coords.end());
    }
    int get(int x) {
        return lower_bound(coords.begin(), coords.end(), x) - coords.begin();
    }
    int size() { return coords.size(); }
};
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int &i : a) {
        cin >> i;
    }

    CoordCompressor CC;
    CC.coords = a;
    CC.build();

    vector<int> marking(n, 0);
    int cnt = 0;
    for (int i = 0 ; i < n; i++) {
        int add_pos = CC.get(a[i]);
        cnt += (marking[add_pos] == 0);
        marking[add_pos]++;
        if (i + 1 >= k) {
            cout << cnt << " ";

            int remove_pos = CC.get(a[i - k + 1]);
            marking[remove_pos]--;
            cnt -= marking[remove_pos] == 0;
        }
    }
    return 0;
}

