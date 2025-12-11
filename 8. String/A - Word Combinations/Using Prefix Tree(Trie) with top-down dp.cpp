/*
    Author : M0stafa
    Topic : String Algorithm
    Algorithm : Trie with DP
    DP trick : Top-Down approach
*/
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int Mod = 1e9 + 7;
struct Node {
    vector<int> next;
    bool end;
    Node() : next(27, -1), end(false) {}
};
struct Trie {
    vector<Node> trie_tree;
    Trie() : trie_tree() {
        trie_tree.emplace_back();
    }
    void insert(string &s) {
        int root = 0;
        for (auto c : s) {
            int nxt = c - 'a';
            if (trie_tree[root].next[nxt] == -1) {
                trie_tree[root].next[nxt] = trie_tree.size();
                trie_tree.emplace_back();
            }
            root = trie_tree[root].next[nxt];
        }
        trie_tree[root].end = true;
    }
};
signed main() {
    string s;
    cin >> s;

    int n;
    cin >> n;

    Trie trie;
    for (int i = 0; i < n; i++) {
        string t;
        cin >> t;
        trie.insert(t);
    }

    n = s.size();
    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        int root = 0;
        for (int j = i; j < n; j++) {
            int nxt = s[j] - 'a';
            if (trie.trie_tree[root].next[nxt] == -1) {
                break;
            }
            root = trie.trie_tree[root].next[nxt];
            if (trie.trie_tree[root].end) {
                dp[j + 1] = (dp[i] + dp[j + 1]) % Mod;
            }
        }
    }
    cout << dp[n];
    return 0;
}
