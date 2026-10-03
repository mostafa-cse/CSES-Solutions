#include <bits/stdc++.h>
using namespace std;

int find(int pos, vector<int>& replacement) {
    return replacement[pos] == pos ? pos : replacement[pos] = find(replacement[pos], replacement);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> tickets(n), replacement(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> tickets[i];
        replacement[i] = i;
    }
    replacement[n] = n;

    sort(tickets.begin(), tickets.end());
    while (m--) {
        int k;
        cin >> k;
        int pos = upper_bound(tickets.begin(), tickets.end(), k) - tickets.begin() - 1;
        if (pos < 0) {
            cout << -1 << '\n';
            continue;
        }
        pos = find(pos, replacement);
        if (pos == n || tickets[pos] > k)
            cout << -1 << '\n';
        else {
            cout << tickets[pos] << '\n';
            replacement[pos] = (pos == 0 ? n : pos - 1);
        }
    }
    return 0;
}
