#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = (1LL << 60);

int solveDNC(const vector<int>& a, int l, int r) {
    if (l == r) return a[l];
    int m = (l + r) >> 1;
    int left = solveDNC(a, l, m);
    int right = solveDNC(a, m+1, r);

    int bestL = -INF, sum = 0;
    for (int i = m; i >= l; --i) sum += a[i], bestL = max(bestL, sum);

    int bestR = -INF; sum = 0;
    for (int i = m+1; i <= r; ++i) sum += a[i], bestR = max(bestR, sum);

    return max({left, right, bestL + bestR});
}
int maxSubarrayDNC(const vector<int>& a) {
    return solveDNC(a, 0, (int)a.size()-1);
}
int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    cout << maxSubarrayDNC(a) << '\n';
    return 0;
}
