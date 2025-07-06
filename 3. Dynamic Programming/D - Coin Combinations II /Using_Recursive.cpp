// This is TLE Solution
#include <bits/stdc++.h>
using namespace std;

#define M 1000000007
vector<int> arr;
vector<vector<int>> dp;
 
int solve(int i, int target) {
	if (i >= (int)arr.size() or target <= 0) {
        return target == 0;
    }
	if (dp[i][target] != -1) {
        return dp[i][target];
    }
	return dp[i][target] = (solve(i, target - arr[i]) % M + solve(i + 1, target) % M) % M;
}
 
int main() {
	int n, target;
	cin >> n >> target;

	arr.resize(n);
	dp.resize(n + 1, vector<int>(target + 1, -1));
	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
	}
	cout << solve(0, target);
    return 0;
}