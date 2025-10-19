#include <bits/stdc++.h>
using namespace std;

#define N 200010
vector<int> g[N];
int c[N];
int b[N];
int siz[N];
int son[N];

void dfs(int x,int fa) {
    siz[x] = 1;
    for(int y : g[x]) {
        if(y == fa) continue;
        dfs(y,x);
        siz[x] += siz[y];
        if(siz[y] > siz[son[x]]) son[x] = y;
    }
}

int tong[N]; // 桶保留数了
int cnt = 0;
void dfs_clear(int x,int fa) {
    --tong[b[x]];
    if(tong[b[x]] == 0) --cnt;
    for(int y : g[x]) {
        if(y == fa) continue;
        dfs_clear(y,x);
    }
}
void dfs_add(int x,int fa) {
    if(tong[b[x]] == 0) ++cnt;
    ++tong[b[x]];
    for(int y : g[x]) {
        if(y == fa) continue;
        dfs_add(y,x);
    }
}
int ans[N];
void dsu(int x,int fa) {
    for(int y : g[x]) {
        if(y == fa || y == son[x]) continue;
        dsu(y,x);
        dfs_clear(y,x);
    }
    if(son[x]) dsu(son[x],x);
    if(tong[b[x]] == 0) ++cnt;
    ++tong[b[x]];
    for(int y : g[x]) {
        if(y == fa || y == son[x]) continue;
        dfs_add(y,x);
    }
    ans[x] = cnt;
}
int n;

#define PII pair<int,int>
PII nos[N];
signed main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> c[i];
    for(int i = 1; i <= n; ++i) nos[i] = {c[i],i};
    sort(nos + 1,nos + 1 + n);
    for(int i = 1; i <= n; ++i) {
        if(nos[i].first == nos[i - 1].first) {
            b[nos[i].second] = b[nos[i - 1].second];
        }else{
            b[nos[i].second] = b[nos[i - 1].second] + 1;
        }
    }
    for(int i = 1; i < n; ++i) {
        int a,b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(1,0);
    dsu(1,0);
    for(int i = 1; i <= n; ++i) cout << ans[i] << " ";
}
