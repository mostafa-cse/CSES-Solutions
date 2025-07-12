#include <bits/stdc++.h>
using namespace std;

int n, q, tab[200009], odp[200009], a, b, u, loopN, koop[200009];
pair<int, int> val[200009], valp[200009];
vector<int> t[200009];

void dfs(int N, int l, int k) {
    val[N] = {l, k};
    if (val[tab[N]].first == 0 && valp[tab[N]].second == 0) {
        dfs(tab[N], l + 1, k);
    } else {
        if (val[tab[N]].second != k) {
            if (valp[tab[N]].second == 0) {
                a = val[tab[N]].first + 1;
                b = val[tab[N]].second;
            } else {
                a = 1;
                b = tab[N];
            }
        } else {
            loopN++;
            b = tab[N];
            valp[b] = {val[N].first - val[tab[N]].first + 1, loopN};
            t[loopN].push_back(b);
            koop[b] = 0;
        }
    }

    if (a != 0) {
        val[N].first = a;
        a++;
    } else {
        if (b != 0) {
            if (b == N) {
                a = 1;
            } else {
                valp[N] = valp[b];
                t[loopN].push_back(N);
                u++;
                koop[N] = u;
            }
        }
    }
    val[N].second = b;
}

int main() {
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> tab[i];
        if (tab[i] == i) {
            loopN++;
            koop[i] = 0;
            t[loopN].push_back(i);
            valp[i] = {1, loopN};
            val[i].second = i;
        }
    }
    for (int i = 1; i <= n; i++) {
        a = 0;
        b = 0;
        u = 0;
        if (val[i].second == 0) {
            dfs(i, 1, i);
        }
    }
    int h, k;
    for (int i = 0; i < q; i++) {
        cin >> h >> k;
        if (valp[h].first != 0) {
            k = k % valp[h].first;
        } else if (k > val[h].first) {
            k = (k - val[h].first) % valp[val[h].second].first;
            h = val[h].second;
        } else {
            for (int i = 0; i < k; i++) {
                h = tab[h];
            }
            cout << h << '\n';
            continue;
        }
        if (koop[h] - k >= 0) {
            cout << t[valp[h].second][koop[h] - k] << '\n';
        } else {
            cout << t[valp[h].second][valp[h].first - abs(koop[h] - k)] << '\n';
        }
    }
}