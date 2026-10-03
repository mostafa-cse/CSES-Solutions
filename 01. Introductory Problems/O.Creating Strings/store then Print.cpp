#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
    string s;
    cin >> s;

    vector<string> ans;
    sort(s.begin(), s.end());
    do {
        ans.push_back(s);
    } while (next_permutation(s.begin(), s.end()));

    cout << ans.size() << endl;
    for (auto s : ans) {
        cout << s << endl;
    }
    return 0;
}