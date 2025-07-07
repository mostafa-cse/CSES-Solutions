#include <bits/stdc++.h>
using namespace std;

void makeSet(int v, vector<int>& parent) { parent[v] = v; }
int findSet(int v, vector<int>& parent) {
    if (v != parent[v])
        parent[v] = findSet(parent[v], parent);
    return parent[v];
}
void unionSets(int u, int v, vector<int>& parent) {
    int root1 = findSet(u, parent);
    int root2 = findSet(v, parent);
    parent[root2] = root1;
}
bool check(int u, int v, vector<int>& parent) {
    return findSet(u, parent) == findSet(v, parent);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n;
    cin >> n;
    vector<int> ori(n);
    vector<pair<int, int>> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> ori[i];
        arr[i].first = ori[i];
        arr[i].second = i + 1;
    }
    sort((arr).begin(), (arr).end());
    vector<int> parent(n + 2);
    for (int i = 0; i < n + 2; i++) {
        makeSet(i, parent);
    }
    vector<int> maxs(n + 2, -1);
    for (int i = 0; i < n; i++) {
        int dir = findSet(arr[i].second + 1, parent);
        int esq = findSet(arr[i].second - 1, parent);
        if (maxs[dir] == -1 && maxs[esq] == -1) {
            maxs[arr[i].second] = 1;
        } else if (maxs[dir] == -1) {
            maxs[arr[i].second] =
                maxs[esq] + (ori[esq - 1] < ori[arr[i].second - 1] ? 1 : 0);
            unionSets(arr[i].second, esq, parent);
        } else if (maxs[esq] == -1) {
            maxs[arr[i].second] =
                maxs[dir] + (ori[dir - 1] < ori[arr[i].second - 1] ? 1 : 0);
            unionSets(arr[i].second, dir, parent);
        } else {
            maxs[arr[i].second] = max(
                maxs[dir] + (ori[dir - 1] < ori[arr[i].second - 1] ? 1 : 0),
                maxs[esq] + (ori[esq - 1] < ori[arr[i].second - 1] ? 1 : 0));
            unionSets(arr[i].second, dir, parent);
            unionSets(arr[i].second, esq, parent);
        }
    }
    cout << maxs[findSet(1, parent)] << endl;
    return 0;
}
