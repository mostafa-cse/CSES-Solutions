// https://cses.fi/problemset/hack/2081/entry/14782110/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define sz(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()

const int N = 2e5 + 7;
const ll MOD = 1e9 + 7;

int n, k1, k2;
int h[N];
ll ans;
vector<int> adj[N];

deque<ll> dfs(int u, int p = 0){
     deque<ll> resu = {1};

     for(int v:adj[u]){
        if(v == p) continue;
        auto resv = dfs(v, u);
        resv.push_front(resv[0]);

        if (sz(resu) < sz(resv)) {
            swap(resu, resv);
        }

        for(int i = 0; i < sz(resv); ++i){
            int p1 = max(0, k1 - i);
            int p2 = max(0, k2 - i + 1);

            ll tmp = resv[i];
            if(i + 1 < sz(resv)) tmp -= resv[i+1];

            if(p1 < sz(resu)) ans += tmp * resu[p1];
            if(p2 < sz(resu)) ans -= tmp * resu[p2];
        }

        for(int i = sz(resv) - 1; i >= 0; --i){
            resu[i] += resv[i];
        }
     }

     return resu;
}

void solve(){
    cin >> n >> k1 >> k2;
    for(int i = 1, u, v; i < n; ++i){
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1);

    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    #ifdef LOCAL
        freopen("test.inp","r",stdin);
        freopen("test.out","w",stdout);
        freopen("test.err","w",stderr);
    #endif
    int ts=1;
    // cin>>ts;
    while(ts--){
        solve();
    }
    return 0;
}
