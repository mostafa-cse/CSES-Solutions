#include <bits/stdc++.h>
using namespace std;
int n, m;
vector<double> work(vector<double> &a) {
	vector<double> rtn(m, 0);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            rtn[max(i, j)] += a[i] / m;
        }
    }
	return rtn;
}
int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m;

    vector<double> a(m, 1.0 / m);
    for (int i = 2; i <= n; i++) {
        a = work(a);
    }

	double ans = 0;
	for (int i = 0; i < m; i++) {
        ans += (i + 1) * a[i];
    }
	cout << setprecision(6) << fixed << ans << '\n';
}
