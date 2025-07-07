#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n;
    cin >> n;

    vector<ll> a(n);
    for (ll i = 0; i < n; ++i) cin >> a[i];

    stack<ll> st;
    st.push(-1); 
    for (ll i = 0; i < n; ++i) {
        while (st.size() > 1 && a[st.top()] >= a[i]) {
            st.pop();
        }
        
        cout << st.top() + 1 << " ";
        st.push(i);
    }

    return 0;
}