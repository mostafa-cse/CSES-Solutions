#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> ans;
    ans.reserve(n);
    vector<int> idx;
    idx.reserve(n);
    vector<int> parent(n, -1);

    for (int i = 0; i < n; i++) {
        // int pos = upper_bound(ans.begin(), ans.end(), a[i]) - ans.begin(); // Greater then or equal
        int pos = lower_bound(ans.begin(), ans.end(), a[i]) - ans.begin(); // greater
        if (pos == (int)ans.size()) {
            ans.push_back(a[i]);
            idx.push_back(i);
        } else {
            ans[pos] = a[i];
            idx[pos] = i;
        }

        if (pos > 0) parent[i] = idx[pos - 1];
    }

    vector<int> lis(ans.size());
    int last = idx.back();
    for (int i = lis.size() - 1; i >= 0; i--) {
        lis[i] = a[last];
        last = parent[last];
    }

    cout << lis.size() << "\n";
    return 0;
}
