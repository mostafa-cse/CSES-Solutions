#include <bits/stdc++.h>
using namespace std;

#define N 200010
vector<int> g[N];
int c[N], sortC[N];
int siz[N];
int son[N];
int n;

void dfs(int u,int p) {
    siz[u] = 1;
    for(int v : g[u]) {
        if(v != p) {
            dfs(v, u);
            siz[u] += siz[v];
            // heavy
            if (siz[v] > siz[son[u]]) {
                son[u] = v;
            }
        }
    }
}
int tong[N], cnt = 0;
void remove(int u,int p) {
    --tong[c[u]];
    cnt -= (tong[c[u]] == 0);
    for(int v : g[u]) {
        if(v != p) {
            remove(v, u);
        }
    }
}
void add(int u,int p) {
    cnt += (tong[c[u]] == 0);
    ++tong[c[u]];
    for(int v : g[u]) {
        if(v != p) {
            add(v, u);
        }
    }
}
int ans[N];
void dsu(int u,int p) {
    for(int v : g[u]) {
        if(v != p and v != son[u]) {
            dsu(v,u);
            remove(v,u);
        }
    }
    if (son[u]) {
        dsu(son[u], u);
    }
    cnt += (tong[c[u]] == 0);
    ++tong[c[u]];

    for(int v : g[u]) {
        if(v != p || v != son[u]) {
            add(v, u);
        }
    }
    ans[u] = cnt;
}

signed main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> c[i];
        sortC[i] = c[i];
    }

    // co-ordinate compression
    sort(sortC + 1, sortC + 1 + n);
    for (int i = 1; i <= n; ++i) {
        c[i] = lower_bound(sortC + 1, sortC + n + 1, c[i]) - sortC - 1;
    }

    for(int i = 1; i < n; ++i) {
        int a,b;
        cin >> a >> b;

        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1,0);

    dsu(1,0);

    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << " ";
    }
    return 0;
}
