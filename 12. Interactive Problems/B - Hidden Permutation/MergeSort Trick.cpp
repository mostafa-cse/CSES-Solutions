#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()
string query(int x, int y) {
    cout << "? " << x << " " << y << endl;
    string s;
    cin >> s;
    return s;
}
void merge(int l, int m, int r, vector<int> &a) {
    int n = a.size();
    vector<int> merge;
    int left = l;
    int right = m;
    while (left < m and right <= r) {
        merge.push_back(query(a[left], a[right]) == "YES" ? a[left++] : a[right++]);
    }

    while (left < m) merge.push_back(a[left++]);
    while (right <= r) merge.push_back(a[right++]);

    for (int i = l; i <= r; i++) {
        a[i] = merge[i - l];
    }
}
void mergeSort(int l, int r, vector<int> &a) {
    if (l >= r) {
        return;
    }
    int m = (l + r) >> 1;
    mergeSort(l, m, a);
    mergeSort(m + 1, r, a);
    merge(l, m + 1, r, a);
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n;
    cin >> n;

    vector<int> a(n + 1);
    iota(all(a), 0);
    mergeSort(1, n, a);

    vector<int> ans(n + 1);
    for (int i = 1; i <= n; i++) {
        ans[a[i]] = i;
    }

    cout << "! ";
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }

    return 0;
}

