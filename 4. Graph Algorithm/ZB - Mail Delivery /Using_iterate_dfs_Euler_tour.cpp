#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<set<int>> a(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        a[x].insert(y);
        a[y].insert(x);
    }
    for (int i = 0; i < n; i++) {
        if (a[i].size() % 2) {
            cout << "IMPOSSIBLE";
            return 0;
        }
    }

    vector<int> ans;
    stack<int> st;
    st.push(0);
    while (!st.empty()) {
        int x = st.top();
        if (a[x].empty()) {
            ans.push_back(x);
            st.pop();
        } else {
            int y = *a[x].begin();
            a[x].erase(y);
            a[y].erase(x);
            st.push(y);
        }
    }
    if (ans.size() != m + 1) {
        cout << "IMPOSSIBLE";
        return 0;
    } else {
        for (auto u : ans) {
            cout << u + 1 << " ";
        }
    }
    return 0;
}
