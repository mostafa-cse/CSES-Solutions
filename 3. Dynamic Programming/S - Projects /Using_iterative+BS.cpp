#include <bits/stdc++.h>
using namespace std;

struct Project {
    int start, end, reward;
};

bool compare(Project &a, Project &b) {
    return a.end < b.end;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    vector<Project> projects(n);
    
    for (int i = 0; i < n; i++) {
        cin >> projects[i].start >> projects[i].end >> projects[i].reward;
    }
    
    sort(projects.begin(), projects.end(), compare);
    
    vector<long long> dp(n + 1, 0);
    vector<int> endTimes(n);
    
    for (int i = 0; i < n; i++) {
        endTimes[i] = projects[i].end;
    }
    
    for (int i = 0; i < n; i++) {
        int idx = upper_bound(endTimes.begin(), endTimes.end(), projects[i].start - 1) - endTimes.begin();
        long long include = projects[i].reward + (idx > 0 ? dp[idx] : 0);
        long long exclude = dp[i];
        dp[i + 1] = max(include, exclude);
    }
    
    cout << dp[n] << endl;
    return 0;
}