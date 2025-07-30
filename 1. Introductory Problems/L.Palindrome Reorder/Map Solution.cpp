#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    string s;
    cin >> s;

    map<char, int> mark;
    for (char c : s) {
        mark[c]++;
    }

    int cnt = 0;
    for (auto [f, s] : mark) {
        cnt += (s & 1) == 1;
        if (cnt == 2) {
            return cout << "NO SOLUTION", 0;
        }
    }

    string first = "", last = "", one = "";
    for (auto [f,s] : mark) {
        for (int i = 0; i < s / 2; i++) {
            first += f;
            last += f;
        }
        if (s & 1) {
            one += f;
        }
    }
    reverse(last.begin(), last.end());
    cout << first << one << last;
    return 0;
}