#include <bits/stdc++.h>
using namespace std;
int n;
struct Point{
	long long x, y;
}arr[100005];

// Shoelace formula
long long area(Point *arr) {
	long long res = 0;
	int j = n;
	for (int i = 1; i <= n; i++) {
		res += (arr[j].x + arr[i].x) * (arr[j].y - arr[i].y);
		j = i;
	}
  	return abs(res);
}

signed main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i].x >> arr[i].y;
	}

	cout << area(arr);

	return 0;
}
