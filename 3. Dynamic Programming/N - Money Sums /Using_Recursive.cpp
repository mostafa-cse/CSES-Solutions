#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,a[101];
set<int>st;
int i = 0;
bool dp[101][100005];
int memoi(int N,int sum,vector<vector<int>> &dp) {
    i ++ ;
    if(N == 0) {
        if(sum)
            st.insert(sum);
        return 1;
    }
    if(dp[N][sum] != -1) {
        return dp[N][sum];
    }
    return dp[N][sum] = memoi(N - 1,sum + a[N], dp) + memoi(N - 1, sum, dp);
}
int32_t main() {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);  cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    vector<vector<int> >dp(101,vector<int>(100001, -1));
    memoi(n, 0, dp);
    cout << st.size() << endl;
    
    for(auto ele : st) {
        cout << ele << " ";
    }
    return 0;
}