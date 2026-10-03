#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()
struct State {
    map<char, int> next;
    int len;
    int link;
};
struct SuffixAutomaton {
    vector<State> states;
    int last;
    SuffixAutomaton() {
        states.push_back({{}, 0, -1}); // Root: len 0, link -1
        last = 0;
    }
    void add_char(char c) {
        int cur = states.size();
        states.push_back({{}, states[last].len + 1, 0});

        int p = last;
        while (p != -1 && !states[p].next.count(c)) {
            states[p].next[c] = cur;
            p = states[p].link;
        }

        if (p == -1) {
            states[cur].link = 0;
        } else {
            int q = states[p].next[c];
            if (states[p].len + 1 == states[q].len) {
                states[cur].link = q;
            } else {
                int clone = states.size();
                states.push_back({states[q].next, states[p].len + 1, states[q].link});

                while (p != -1 && states[p].next[c] == q) {
                    states[p].next[c] = clone;
                    p = states[p].link;
                }
                states[q].link = clone;
                states[cur].link = clone;
            }
        }
        last = cur;
    }

    bool check(string &pat) {
        int cur = 0;
        for (char c : pat) {
            if (states[cur].next.count(c) == 0) {
                return false;
            }
            cur = states[cur].next[c];
        }
        return true;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    string txt;
    cin >> txt;

    SuffixAutomaton sam;
    for (auto el : txt) {
        sam.add_char(el);
    }

    int q;
    cin >> q;
    while (q--) {
        string t;
        cin >> t;
        cout << (sam.check(t) ? "YES" : "NO") << endl;
    }
    return 0;
}
