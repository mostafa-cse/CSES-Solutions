#include <bits/stdc++.h>
#define int long long
using namespace std;
const int M = 1e6 + 5;
int spf[M];
void seive() {
    for (int i = 0; i < M; i++) {
        spf[i] = i;
    }
    for (int i = 2; i * i <= M; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j < M; j += i) {
                if (spf[j] == j) {
                    spf[j] = i;
                }
            }
        }
    }
}
signed main() {
    int n;
    cin >> n;

    seive();

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    unordered_map<int, int> total;
    int possible_pair = 0;
    for (int el : a) {
        vector<int> prime;
        while (spf[el] != 1) {
            prime.push_back(spf[el]);
            el /= spf[el];
        }
        if (el != 1) {
            prime.push_back(el);
        }
        sort(prime.begin(), prime.end());
        prime.resize(unique(prime.begin(), prime.end()) - prime.begin());

        for (int mask = 1; mask < (1 << prime.size()); mask++) {
            int mul = 1, cnt = 0;
            for (int b = 0; b < prime.size(); b++) {
                if (mask >> b & 1) {
                    mul *= prime[b];
                    cnt++;
                }
            }
            int val = total[mul];
            if (~cnt & 1) val *= -1;
            possible_pair += val;
            total[mul]++;
        }
    }
    cout << (n * (n - 1) / 2) - possible_pair;
    return 0;
}
