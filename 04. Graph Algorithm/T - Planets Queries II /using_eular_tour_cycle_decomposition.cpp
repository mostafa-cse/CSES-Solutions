#include <bits/stdc++.h>
using namespace std;
const int SIZE = 2e5 + 5;
int timer = 1, root, parent[SIZE], lev[SIZE], c[SIZE], s[SIZE];
int ID[SIZE], cycSize[SIZE], in[SIZE], out[SIZE]; bool cycle[SIZE];
void dfs(int node, int depth) {
    lev[node] = depth;
    ID[node] = root;
    int cN = c[node];
    in[node] = timer++;
    while (cN) {
        if (cN != root) dfs(cN, depth + 1);
        cN = s[cN];
    }
    out[node] = timer++;
}
 
bool checkAncestor(int a, int b) {
    return in[a] >= in[b] && out[a] <= out[b];
}
 
int main() {
    int n, q;
    int a, b, p1, p2, p;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        cin >> parent[i]; 
        p = parent[i];
        if (c[p]) {
            s[i] = s[c[p]], s[c[p]] = i;
        } else {
            c[p] = i;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (ID[i]) continue;
        p1 = p2 = i;
        do {
            p1 = parent[parent[p1]];
            p2 = parent[p2];
        } while (p1 != p2);

        do {
            cycle[p1] = true;
            p1 = parent[p1];
            cycSize[p2]++;
        } while (p1 != p2);
        root = p1; dfs(p1, 0);
    }
    for (int i = 0; i < q; i++) {
        cin >> a >> b;
        if (ID[a] != ID[b]) {
            cout << "-1\n";
        } else if (checkAncestor(a, b)) {
            cout << lev[a] - lev[b] << '\n';
        } else if (cycle[b]){
            cout << lev[a] + cycSize[ID[b]] - lev[b] << '\n';
        } else {
            cout << "-1\n";
        }
    }
    return 0;
}
