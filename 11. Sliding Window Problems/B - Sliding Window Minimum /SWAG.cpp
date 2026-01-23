#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()
int aggregation(int x, int y) {
    // return x | y; // OR
    // return x + y; // SUM
    // return max(x, y); // MAX
    return min(x, y); // MIN
};
struct AggStack {
    stack<pair<int, int>> st;

    void Push(int x) {
        int cur = -1;
        if (st.empty()) {
            cur = x;
        } else {
            cur = aggregation(x, st.top().second);
        }
        st.push({x, cur});
    }

    int Empty() {
        return st.empty();
    }

    void Pop() {
        st.pop();
    }

    int Query() const {
        return st.top().second;
    }
};

struct AggQueue {
    AggStack IN, OUT;

    void Push(int x) {
        IN.Push(x);
    }

    void Pop() {
        if (OUT.Empty()) {
            while (!IN.Empty()) {
                int val = IN.st.top().first;
                IN.Pop();
                OUT.Push(val);
            }
        }
        OUT.Pop();
    }

    int Query() {
        if (IN.Empty()) return OUT.Query();
        if (OUT.Empty()) return IN.Query();
        return aggregation(IN.Query(), OUT.Query());
    }
};
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, k;
    cin >> n >> k;

    int x, a, b, c;
    cin >> x >> a >> b >> c;

    vector<int> ar = {x};
    for (int i = 1; i < n; i++) {
        int cur = (ar[i - 1] * a + b) % c;
        ar.push_back(cur);
    }

    AggQueue swag;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        swag.Push(ar[i]);
        if (i + 1 >= k) {
            sum ^= swag.Query();
            swag.Pop();
        }
    }
    cout << sum << endl;
    return 0;
}

