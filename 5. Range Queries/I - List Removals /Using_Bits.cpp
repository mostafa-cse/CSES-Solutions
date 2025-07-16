#include <bits/stdc++.h>
using namespace std;
struct BIT {
    vector<int> bit;
 
    BIT (int size) { bit.resize(size); }
 
    int get (int i) {
        int sum = 0;
        for ( ; i >= 0; i = (i & (i + 1)) - 1)
            sum += bit[i];
        return sum;
    }
 
    void update(int i, int delta) {
        for ( ; i < bit.size(); i |= (i + 1))
            bit[i] += delta;
    }
 
    void update(int l, int r, int delta) {
        update(l, delta);
        update(r + 1, -delta);
    }
};
 
int n;
vector<int> arr;
int bs (int x, BIT& ft) {
    int l = 0, r = n - 1, m;
    while (l < r) {
        m = (l + r) / 2;
        if (ft.get(m) >= x)
            r = m;
        else 
            l = m + 1;
    }
    return l;
}
int main () {
    cin >> n;
    arr.resize(n);
 
    BIT ft (n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        ft.update(i, 1);
    } 
    
    int x;
    for (int i = 0; i < n; i++) {
        cin >> x;
        int it = bs(x, ft);
        cout << arr[it] << ' ';
        ft.update(it, -1);
    }
    return 0;
}