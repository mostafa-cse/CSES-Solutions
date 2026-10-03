#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

struct HashString {
    const ll A = 31;
    const ll B = 991831889;

    vector<ll> pows, sums;

    HashString(string s) {
        int n = s.size();
        pows.resize(n + 1);
        pows[0] = 1;
        sums.resize(n + 1);
        sums[0] = 0;
        for (int i = 1; i <= n; i++) {
            pows[i] = pows[i - 1] * A % B;
            sums[i] = (sums[i - 1] * A + s[i - 1]) % B;
        }
    }

    ll hash(int a, int b) {
        ll h = sums[b + 1] - sums[a] * pows[b - a + 1];
        return (h % B + B) % B;
    }
};

int main() {
    string s;
    cin >> s;
    int n = s.size();

    HashString h(s);
    for (int i = 1; i < n; i++) {
        cerr << i << " " << n - 1 << endl;
        cerr << 0 << " " << n - i - 1 << endl;
        cerr << endl;
        if (h.hash(i, n - 1) == h.hash(0, n - i - 1)) {
            cout << i << " ";
        }
    }
    cout << n << "\n";
}
