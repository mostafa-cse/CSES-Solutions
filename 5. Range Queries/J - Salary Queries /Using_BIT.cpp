#include <bits/stdc++.h>
#define all(a) a.begin(), a.end()
using namespace std;
 
struct BIT {
    vector<int> bit;
 
    BIT () { bit.resize((int) 6e5); }
 
    int get(int i) {
        int sum = 0;
        for ( ; i >= 0; i = (i & (i + 1)) - 1)
            sum += bit[i];
        return sum;
    }
 
    void update(int i, int delta) {
        for ( ; i < bit.size(); i |= (i + 1))
            bit[i] += delta;
    }
 
    int get (int l, int r) { return get(r) - get(l - 1); }
};
 
BIT ft;
int n, q;
vector<int> arr;
vector<pair<int, int>> comp;
int cast(int x) {
    auto lb = lower_bound(all(comp), pair<int, int> (x, 0));
    return (*lb).second;
}
 
struct Query {
    char t;
    int a, b;
 
    void execute () {
        if (t == '!') {
            ft.update(cast(arr[a]), -1);
            arr[a] = b;
            ft.update(cast(arr[a]), 1);    
            return;
        }
 
        cout << ft.get(cast(a), cast(b)) << '\n';
    }
};
vector<Query> qr;
int main () {
    cin >> n >> q;
    arr.resize(n);
 
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        comp.push_back({arr[i], 0});
    }
 
    char t;
    int a, b;
    for (int i = 0; i < q; i++) {
        cin >> t >> a >> b;
        if (t == '!') {
            a--;
            comp.push_back({b, 0});
        }
        else {
            comp.push_back({a, 0});
            comp.push_back({b, 0});
        }
 
        qr.push_back({t, a, b});
    }
    sort(all(comp));
 
    int cnt = 0;
    for (int i = 0; i < comp.size(); i++) {
        if (i && comp[i - 1].first != comp[i].first)
            cnt++;
        
        comp[i].second = cnt;
    }
 
    for (int i : arr) {
        ft.update(cast(i), 1);
    }
 
    for (Query& it : qr) {
        it.execute();
    }
    return 0;
}