#include <bits/stdc++.h>
using namespace std ;
 
int dfs(int i , vector<list<int>>&graph , vector<int>&dp){
    if(dp[i] != -1) return dp[i] ;
    for(int &a : graph[i]){
        dp[i] = max(dp[i], dfs(a,graph,dp)+1);
    }
    if(dp[i]==-1)dp[i]=0;
    return dp[i];
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n ;
    cin>>n ;
 
    vector<int>nums(n);
    for(int i=0 ;i<n ; i++)cin>>nums[i];
 
    stack<pair<int,int>>s ;
    vector<list<int>>graph(n);
 
    for(int i=0 ; i<n ; i++){
        while(!s.empty() && s.top().second<nums[i]){
            graph[i].push_back(s.top().first);
            s.pop();
        } 
        s.emplace(i,nums[i]);
    }
    while(!s.empty())s.pop();
 
    for(int i=n-1 ; i>=0 ; i--){
        while(!s.empty() && s.top().second<nums[i]){
            graph[i].push_back(s.top().first);
            s.pop();
        } 
        s.emplace(i,nums[i]);
    }
    while(!s.empty())s.pop();
 
    vector<int>dp(n,-1);
    int ans = 0 ;
 
    for(int i=0 ; i<n ; i++){
        ans = max(ans,dfs(i,graph,dp)+1);
    }
 
    cout<<ans<<'\n';
}