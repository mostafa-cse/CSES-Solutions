#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define pb push_back

vector<int> manacher(string s){
    string t;
    for(auto c: s){
        t += '#'; t += c;
    }
    t += '#';
    int n = sz(t);
    t = "$" + t + "^";
    vector<int> d(n+1);
    int l = 0, r = 1;
    for(int i=1; i<=n; i++){
        d[i] = min(r-i, d[l+r-i]);
        while(t[i-d[i]] == t[i+d[i]]) d[i]++;
        if(i+d[i] > r){
            l = i-d[i], r = i+d[i];
        }
    }
    d.erase(begin(d));
    return d;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    string s; cin >> s;
    auto d = manacher(s);
    int n = sz(s);
    vector<pair<int, int>> L[n], R[n];
    for(int i=0; i<=2*n; i++){
        int l = d[i]-1;
        if(l == 0) continue;
        int a = (i-l)/2, b = (i+l)/2-1;
        L[a].pb({i/2, l%2}); R[b].pb({i/2, l%2});
    }
    vector<int> ans(n);
    set<int> st0, st1;
    for(int i=0; i<n; i++){
        for(auto [j, t]: L[i]){
            if(t == 0) st0.insert(j);
            else st1.insert(j);
        }
        if(!st0.empty()){
            int j = *st0.begin();
            ans[i] = max(ans[i], 2*(i-j+1));
        }
        if(!st1.empty()){
            int j = *st1.begin();
            ans[i] = max(ans[i], 2*(i-j+1)-1);
        }
        for(auto [j, t]: R[i]){
            if(t == 0) st0.erase(j);
            else st1.erase(j);
        }
    }
    for(int i=0; i<n; i++) cout << ans[i] << ' ';
}
