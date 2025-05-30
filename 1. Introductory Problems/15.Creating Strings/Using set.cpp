#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
    string s;
    cin >> s;

    set<string> ans;
    // map<string, bool> ans;
    do {
        ans.insert(s);
        // ans[s] = true;
    } while (next_permutation(s.begin(), s.end()));

    cout << ans.size() << endl;
    // for (auto [f, s] : ans) {
    for (auto s : ans) {
        cout << s << endl;
    }
    return 0;
}