#include <bits/stdc++.h>
#define int long long
using namespace std;

class SCCmaker {
    vector<vector<int>> DAG;
    vector<int> info;
    int number_of_nodes;

    void dfs(int node, vector<vector<int>> &adj, vector<int> &vis, vector<int> &order) {
        vis[node] = 1;
        for (auto &i : adj[node]) {
            if (vis[i] != 1) {
                dfs(i, adj, vis, order);
            }
        }
        order.push_back(node);
    }
    void dfs2(int node, vector<vector<int>> &revadj, vector<int> &temp, vector<int> &vis) {
        vis[node] = 1;
        temp.push_back(node);
        for (auto &i : revadj[node]) {
            if (vis[i] == 0) {
                dfs2(i, revadj, temp, vis);
            }
        }
    }

public:
    SCCmaker(vector<vector<int>> &adj, vector<int> &information, vector<pair<int, int>> &edges, int n) {
        vector<int> order;
        vector<int> vis(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            if (!vis[i])
                dfs(i, adj, vis, order);
        }

        reverse(order.begin(), order.end());
        vector<int> vis2(n + 1, 0);
        vector<vector<int>> revadj(n + 1);
        for (auto &i : edges) {
            revadj[i.second].push_back(i.first);
        }

        vector<int> parentset(n + 1, 0);
        int c = 0;
        for (auto &i : order) {
            if (!vis2[i]) {
                vector<int> temp;
                dfs2(i, revadj, temp, vis2);
                int z = temp.size();
                for (int j = 0; j < z; j++) {
                    parentset[temp[j]] = c;
                }
                int sum = combine(temp, information);
                info.push_back(sum);
                c++;
            }
        }
        DAG.resize(c);
        number_of_nodes = c;
        for (auto &i : edges) {
            if (parentset[i.first] != parentset[i.second]) {
                DAG[parentset[i.first]].push_back(parentset[i.second]);
            }
        }
    }
    int combine(vector<int> &temp, vector<int> &information) {
        int sum = 0;
        for (auto &i : temp) {
            sum += information[i - 1];
        }
        return sum;
    }
    vector<vector<int>> getDAG() {
        return DAG;
    }
    vector<int> getinfo() {
        return info;
    }

    int get_numberofnodes() {
        return number_of_nodes;
    }
};
int solve(int node, vector<vector<int>> &DAG, vector<int> &DAGinfo, vector<int> &dp) {
    if (dp[node] != -1) {
        return dp[node];
    }
    int res = 0;
    for (auto &i : DAG[node]) {
        res = max(res, solve(i, DAG, DAGinfo, dp));
    }
    return dp[node] = (res + DAGinfo[node]);
}
int32_t main() {
    int n, m;
    cin >> n >> m;
    vector<int> val(n);
    for (auto &i : val) {
        cin >> i;
    }
    vector<vector<int>> adj(n + 1);
    vector<pair<int, int>> edges;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        edges.push_back({x, y});
        adj[x].push_back(y);
    }
    SCCmaker sccmaker(adj, val, edges, n);
    int DAGnodes = sccmaker.get_numberofnodes();

    vector<vector<int>> DAG = sccmaker.getDAG();
    vector<int> DAGinfo = sccmaker.getinfo();
    vector<int> dp(DAGnodes + 1, -1);

    int res = 0;
    for (int i = 0; i < DAGnodes; i++) {
        res = max(res, solve(i, DAG, DAGinfo, dp));
    }
    cout << res << "\n";
    return 0;
}