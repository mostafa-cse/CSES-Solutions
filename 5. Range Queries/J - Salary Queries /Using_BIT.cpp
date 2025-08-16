#include <bits/stdc++.h>
#define all(a) a.begin(), a.end()
using namespace std;
 
struct BIT {
    vector<int> bit;
    BIT () { bit.resize((int) 6e5); }
    int get(int i) {
        int sum = 0;
        for (; i >= 0; i = (i & (i + 1)) - 1) {
            sum += bit[i];
        }
        return sum;
    }
    void update(int i, int delta) {
        for (; i < bit.size(); i |= (i + 1)) {
            bit[i] += delta;
        }
    }
    int get(int l, int r) { 
        return get(r) - get(l - 1); 
    }
};

int main () {
    int n, q;
    cin >> n >> q;

    vector<int> ar(n), comp;
    for (int i = 0; i < n; i++) {
        cin >> ar[i];
        comp.push_back(ar[i]);
    }

    struct Query {
        char t;
        int a, b;
    };
    vector<Query> qr(q);

    for (int i = 0; i < q; i++) {
        cin >> qr[i].t >> qr[i].a >> qr[i].b;
        if (qr[i].t == '!') {
            qr[i].a--;
            comp.push_back(qr[i].b);
        } else {
            comp.push_back(qr[i].a);
            comp.push_back(qr[i].b);
        }
    }
    sort(all(comp));
    comp.resize(unique(comp.begin(), comp.end()) - comp.begin());

    function<int(int)> cast = [&](int x) -> int {
        return lower_bound(all(comp), x) - comp.begin();
    };

    BIT ft;
    for (int i : ar) {
        ft.update(cast(i), 1);
    }
 
    for (auto &[t, a, b] : qr) {
        if (t == '!') {
            ft.update(cast(ar[a]), -1);
            ar[a] = b;
            ft.update(cast(ar[a]), 1);    
        } else {
            cout << ft.get(cast(a), cast(b)) << '\n';
        }
    }
    return 0;
}