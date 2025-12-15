#include <bits/stdc++.h>

using ll = long long;
using namespace std;

struct SuffixAutomata {

    static constexpr size_t ALPHABET_SIZE = 26;
    static constexpr char ALPHABET_START = 'a';
    static constexpr size_t MAX_LEN = 1'000'001;

    struct State {
        int len, link, last = -1;
        int next[ALPHABET_SIZE];

        void copy(const State &x) {
            len = x.len;
            link = x.link;
            for (size_t i = 0; i < ALPHABET_SIZE; i++) {
                next[i] = x.next[i];
            }
        }

        int &operator[](char c) {
            return next[c-ALPHABET_START];
        }
    };

    State st[2 * MAX_LEN + 1];
    int next_index, last;

    SuffixAutomata() {
        st[1].len = st[1].link = 0;
        next_index = 2;
        last = 1;
    }

    void append(char c, int idx) {
        int cur = next_index++;
        st[cur].last = idx;
        st[cur].len = st[last].len + 1;
        int p = last;
        while (p && !st[p][c]) {
            st[p][c] = cur;
            p = st[p].link;
        }
        if (p) {
            int q = st[p][c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = next_index++;
                st[clone].copy(st[q]);
                st[clone].len = st[p].len + 1;
                while (p && st[p][c] == q) {
                    st[p][c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        } else {
            st[cur].link = 1;
        }
        last = cur;
    }

    void calc(const string &s) {
        vector<int> indices;
        for (int i = 1; i < next_index; i++) {
            indices.emplace_back(i);
        }
        sort(indices.begin(), indices.end(), [&](int a, int b) {
            return st[a].len > st[b].len;
        });
        for (int i : indices) {
            st[st[i].link].last = max(st[st[i].link].last, st[i].last);
        }

        int u = 1;
        for (int i = 0; i < int(s.size()) - 1; i++) {
            u = st[u][s[i]];
            if (st[u].last == int(s.size())) cout << i + 1 << " ";
        }
        cout << "\n";
    }

} sa;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    string s;
    cin >> s;

    for (size_t i = 0; i < s.size(); i++)
        sa.append(s[i], i + 1);
    sa.calc(s);
    return 0;
}
// https://cses.fi/problemset/hack/1732/entry/8595525/
// https://cses.fi/problemset/hack/1732/entry/5623133/
// https://cses.fi/problemset/hack/1732/entry/11125724/
