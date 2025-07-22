#include <bits/stdc++.h>
using  namespace std;
 
#define int long long
const int N = 1e5+9 , INF = 2e9+7;
vector <int> adj[N] , adjr[N] , g[N] , f;
int k[N] , c[N]  , dp[N] , coin[N] , cnt=0;
bool  mrk[N] ;
 
void dfs(int v){
    mrk[v]=1;
    for(int u : adj[v]){
        if(!mrk[u]){
            dfs(u);
        }
    }
    f.push_back(v);
}
void dfsr(int v){
    c[v]=cnt;
    coin[c[v]]+=k[v];
    for(int u : adjr[v]){
        if(!c[u]){
            dfsr(u);
        }
        else if(c[u]!=c[v]){
            g[c[u]].push_back(c[v]);
        }
    }
}
 
int32_t main(){
    int n , m;
    cin >> n >> m;
    for(int i=1 ; i<=n ; i++){
        cin >> k[i];
    }
    for(int i = 0 ; i<m ; i++){
        int u , v;
        cin >> u >> v;
        adj[u].push_back(v);
        adjr[v].push_back(u);
    }
    for(int i=1 ; i<=n ; i++){
        if(!mrk[i]){
            dfs(i);
        }
    }
    for(int i=n-1 ; i>=0 ; i--){
        if(!c[f[i]]){
            cnt++;
            dfsr(f[i]);
        }
    }
    for(int i=n ; i>0 ; i--){
        dp[i]=coin[i];
        for(int u : g[i]){
            dp[i]=max(dp[i] , dp[u]+coin[i]);
        }
    }
    cout << *max_element(dp+1 , dp+n+1) ;
}
