#include <bits/stdc++.h>
using namespace std;
#define int long long
int32_t main() {
    int n;
    cin >> n;
    if (n == 1) {
        cout << "01\n";
        return 0;
    }

    int N = (1 << (n - 1)) - 1;
    vector<vector<int>> adj(N + 1);
    vector<int> indeg(N + 1), outdeg(N + 1);
    for (int i = 0; i <= N; i++) {
        int num1 = (i * 2) % (1 << (max(0ll, (n - 1))));
        int num2 = ((i * 2) + 1) % (1 << (max(0ll, (n - 1))));
        adj[i].push_back(num1);
        adj[i].push_back(num2);
        outdeg[i] += 2;
        indeg[num1]++;
        indeg[num2]++;
    }

    // determine eular path
    vector<int> path;
    stack<int> st;
    st.push(0);
    while (st.size() > 0) {
        int x = st.top();
        if ((indeg[x] == 0) && (outdeg[x] == 0)) {
            path.push_back(x);
            st.pop();
        } else {
            int k = adj[x].back();
            adj[x].pop_back();
            indeg[k]--;
            outdeg[x]--;
            st.push(k);
        }
    }
    reverse(path.begin(), path.end());
    string res = "";
    for (int i = 0; i < n - 1; i++) {
        res += '0';
    }

    for (int i = 0; i < path.size() - 1; i++) {
        if (path[i + 1] == ((path[i] * 2) % (1 << (max(0ll, (n - 1)))))) {
            res += '0';
        } else {
            res += '1';
        }
    }
    cout << res;
    return 0;
}