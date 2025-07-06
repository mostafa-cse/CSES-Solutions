#include <bits/stdc++.h>
using namespace std;

struct maxnum {
    priority_queue<int> num, del;

    void push(int x) { num.push(x); }

    void redel() {
        while (!num.empty() && !del.empty()) {
            int t = num.top();
            int d = del.top();
            if (t != d)
                break;
            num.pop();
            del.pop();
        }
    }

    void erase(int x) { del.push(x); }

    int val() {
        redel();
        if (num.empty())
            return 0;
        return num.top();
    }
} v;

const int N = 2e5 + 10;
int a[N], b[N];
vector<int> p[N];
int n, m;
long long ans;

void add(int i) {
    if (p[i].size() > 1) {
        v.push(p[i][p[i].size() - 2]);
    }
}

void del(int i) {
    if (p[i].size() > 1) {
        v.erase(p[i][p[i].size() - 2]);
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        b[i] = a[i];
    }

    sort(b + 1, b + n + 1);
    m = unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1; i <= n; ++i) {
        a[i] = lower_bound(b + 1, b + m + 1, a[i]) - b;
        p[a[i]].push_back(i);
    }

    for (int i = 1; i <= n; ++i) {
        add(i);
    }

    for (int r = n; r >= 1; --r) {
        int u = v.val() + 1;
        ans += r - u + 1;
        del(a[r]);
        p[a[r]].pop_back();
        add(a[r]);
    }

    cout << ans;
    return 0;
}