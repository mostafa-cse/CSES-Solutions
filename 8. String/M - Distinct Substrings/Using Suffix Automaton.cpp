#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()
struct State {
    map<char, int> next;
    int len;
    int link ;
    int count = 0;
};
struct SuffixAutomaton {
    vector<State> states;
    int last;
    SuffixAutomaton() {
        states.push_back({{}, 0, -1, 0}); // Root: len 0, link -1
        last = 0;
    }
    void add_char(char c) {
        int cur = states.size();
        states.push_back({{}, states[last].len + 1, 0, 0});

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
                states.push_back({states[q].next, states[p].len + 1, states[q].link, 0});

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
    void build(string &txt) {
          for (char c : txt) {
            add_char(c);
        }
        dfs(0);
    }
    void dfs(int v) {
        if (states[v].count) {
            return;
        }
        states[v].count = 1;
        for (auto [c, u] : states[v].next) {
            dfs(u);
            states[v].count += states[u].count;
        }
    }
};
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    string s;
    cin >> s;

    SuffixAutomaton sam;
    sam.build(s);
    cout << sam.states[0].count - 1 << endl;
    return 0;
}
