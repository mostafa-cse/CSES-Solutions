#include<bits/stdc++.h>
using namespace std;

int check(int pos, vector<int> &replacement){
    if (pos < 0 || pos >= replacement.size())
        return -1;

    if (replacement[pos] == -2){
        replacement[pos] = pos - 1;
        return pos;
    }
    replacement[pos] = check(replacement[pos], replacement);
    return replacement[pos];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> tickets(n), replacement(n, -2);
    for (int i = 0; i < n; i++){
        cin >> tickets[i];
    }

    sort(tickets.begin(), tickets.end());
    while (m--){
        int k;
        cin >> k;
        int pos = upper_bound(tickets.begin(), tickets.end(), k) - tickets.begin() - 1;
        if (pos < 0) {
            cout << -1 << endl;
            continue;
        }
        int index = check(pos, replacement);
        if (index < 0 || index >= n || tickets[index] > k)
            cout << -1 << endl;
        else
            cout << tickets[index] << endl;
    }
    return 0;
}
