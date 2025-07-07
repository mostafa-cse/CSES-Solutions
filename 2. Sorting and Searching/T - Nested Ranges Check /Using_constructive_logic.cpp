#include<bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()
string cdn[2] = {"YES", "NO"};
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
class Range{
public:
    int left, right, index;
    bool operator<(const Range &other) const{
        if (left == other.left) {
            return right > other.right;
        }
        return left < other.left;
    }
};
int32_t main() {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);  cout.tie(0);
    int n;
    cin >> n;

    Range a[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i].left >> a[i].right;
        a[i].index = i;
    }
    sort(a, a + n);
    
    vector<int> contains(n, 0);
    for (int i = n - 1, RightVal = 2e9; i >= 0; i--) {
        if (RightVal <= a[i].right) {
            contains[a[i].index] = 1;
        } else {
            RightVal = a[i].right;
        }
    }
    for (int i = 0; i < n; ++i) cout << contains[i] << " \n"[i == n - 1];

    vector<int> contained(n, 0);
    for (int i = 0, RightVal = 0; i < n; i++) {
        if (a[i].right <= RightVal) {
            contained[a[i].index] = 1;
        } else {
            RightVal = a[i].right;
        }
    }
    for (int i = 0; i < n; ++i) cout << contained[i] << " ";
    return 0;
}
