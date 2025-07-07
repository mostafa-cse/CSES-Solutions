#include<bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()

int32_t main() {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);  cout.tie(0);
    int n;
    cin >> n;

    struct Task{
        int duration;
        int deadline;
        bool operator<(const Task &other) const{
            return duration < other.duration;
        }
    };
    vector<Task> a(n);
    for (auto &el : a) {
        cin >> el.duration >> el.deadline;
    }
    sort(all(a));

    int ans = 0, times = 0;
    for (auto el : a) {
        times += el.duration;
        ans += el.deadline - times;
    }
    cout << ans;
    return 0;
}
