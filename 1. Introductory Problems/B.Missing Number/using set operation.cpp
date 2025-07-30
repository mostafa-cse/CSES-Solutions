#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    set<int> st;
    for (int i = 1; i <= n; i++) {
        st.insert(i);
    }

    for (int i = 1; i < n; i++) {
        int x;
        cin >> x;
        st.erase(x);
    }
    cout << *st.begin() << endl;
    return 0;
}
