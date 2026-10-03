#include <bits/stdc++.h>
using namespace std;

struct PalindromicTree {
    struct node {
        array<int, 26> nxt;
        int len;
        int st, en;
        int link;
        int cnt;
        int oc;
        node() { len = st = en = link = cnt = oc = 0; }
    };

    string s;
    vector<node> t;
    int sz;
    int last;

    PalindromicTree() {}

    PalindromicTree(string _s) {
        s = _s;
        int n = s.size();
        t.clear();
        t.resize(n + 9);
        sz = 2;
        last = 2;
        t[1].len = -1;
        t[1].link = 1;
        t[2].len = 0;
        t[2].link = 1;
    }

    int extend(int pos) {
        int cur = last;
        int curlen = 0;
        int ch = s[pos] - 'a';

        while (true) {
            curlen = t[cur].len;
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) break;
            cur = t[cur].link;
        }

        if (t[cur].nxt[ch]) {
            last = t[cur].nxt[ch];
            t[last].oc++;
            return 0;
        }
        sz++;
        last = sz;
        t[sz].oc = 1;
        t[sz].len = t[cur].len + 2;
        t[cur].nxt[ch] = sz;
        t[sz].en = pos;
        t[sz].st = pos - t[sz].len + 1;

        if (t[sz].len == 1) {
            t[sz].link = 2;
            t[sz].cnt = 1;
            return 1;
        }

        while (true) {
            cur = t[cur].link;
            curlen = t[cur].len;
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) {
                t[sz].link = t[cur].nxt[ch];
                break;
            }
        }
        t[sz].cnt = 1 + t[t[sz].link].cnt;
        return 1;
    }

    void calc_occurrences() {
        for (int i = sz; i >= 3; --i) {
            t[t[i].link].oc += t[i].oc;
        }
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
        string s;
    cin >> s;
    PalindromicTree tree(s);
    for (int i = 0; i < s.size(); i++) {
        tree.extend(i);
    }

    array<int, 3> mx = {-1, -1, -1};
    for (int i = 3; i <= tree.sz; i++) {
        auto node = tree.t[i];
        mx = max(mx, array<int, 3>{node.len, node.st, node.en});
    }
    cout << s.substr(mx[1], mx[0]);
    return 0;
}
