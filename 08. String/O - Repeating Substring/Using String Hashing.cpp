#include <iostream>
#include <map>
#include <vector>
using namespace std;

struct SuffixAutomaton {
    struct State {
        int len;
        State *link;
        map<char, State *> next;
        bool final;
        int count;
        int max;
    };

    State *first, *last;
    SuffixAutomaton(string s) {
        first = last = new State{};
        for (auto c : s) {
            auto *add = new State{};
            add->len = last->len + 1;
            add->link = first;
            State *cur = last;
            while (cur && !cur->next[c]) {
                cur->next[c] = add;
                cur = cur->link;
            }
            if (cur && cur->next[c] != add) {
                State *mid = cur->next[c];
                if (cur->len + 1 == mid->len) {
                    add->link = mid;
                } else {
                    auto *copy = new State(*mid);
                    copy->len = cur->len + 1;
                    add->link = mid->link = copy;
                    while (cur && cur->next[c] == mid) {
                        cur->next[c] = copy;
                        cur = cur->link;
                    }
                }
            }
            last = add;
        }
        State *cur = last;
        while (cur->len) {
            cur->final = true;
            cur = cur->link;
        }
        dfs(first);
    }

    void dfs(State *cur) {
        if (cur->count) return;
        if (cur->final) cur->count = 1;
        for (auto [c, p] : cur->next) {
            dfs(p);
            cur->count += p->count;
            if (p->count > 1) {
                cur->max = max(cur->max, p->max + 1);
            }
        }
    }
};

int main() {
    string s;
    cin >> s;
    SuffixAutomaton sa(s);

    auto cur = sa.first;
    if (cur->max == 0) {
        cout << "-1\n";
    } else {
        while (cur->max) {
            for (auto [c, p] : cur->next) {
                if (p->max == cur->max - 1) {
                    cout << c;
                    cur = p;
                    break;
                }
            }
        }
        cout << "\n";
    }
}
