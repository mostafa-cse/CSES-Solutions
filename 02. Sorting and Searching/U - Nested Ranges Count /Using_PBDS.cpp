#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> PBDS;
#define int long long

struct Node{
    int left, right, index;
    bool operator<(const Node &other) const{
        if (left == other.left) {
            return right > other.right;
        }
        return left < other.left;
    }
};
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;

    vector<Node> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].left >> a[i].right;
        a[i].index = i;
    }
    sort(a.begin(), a.end());

    vector<int> contains(n, 0);
    PBDS st;
    map<int, int> cnt;
    for (int i = n - 1; i >= 0; i--) {
        contains[a[i].index] = st.order_of_key(a[i].right) + cnt[a[i].right];
        st.insert(a[i].right);
        cnt[a[i].right]++;
    }
    for (int i = 0; i < n; ++i) cout << contains[i] << " \n"[i == n - 1];

    vector<int> contained(n, 0);
    st.clear();
    for (int i = 0; i < n; i++) {
        contained[a[i].index] = st.size() - st.order_of_key(a[i].right);
        st.insert(a[i].right);
    }
    for (int i = 0; i < n; i++) cout << contained[i] << " ";
    return 0;
}
