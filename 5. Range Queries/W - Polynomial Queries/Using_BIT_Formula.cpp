#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5;
int fena[N+5], fenb[N+5], fenc[N+5];
int n, q;
void update(int fen[], int id, int val) {
    while(id<=N) {
        fen[id] += val;
        id += id&-id;
    }
}
void UpdateRange(int l, int r) {
    // id^2 + (-2l + 3) id  + (l^2 -3l +2)
    int a = 1;
    int b = -2*l+3;
    int c = l*l-3*l + 2;

    update(fena, l, a);
    update(fena, r+1, -a);
    update(fenb, l, b);
    update(fenb, r+1, -b);
    update(fenc, l, c);
    update(fenc, r+1, -c);

    //  r^2 - 2*r*l + 3r -l + 2
    int cc = (r-l+1)*(l + r)  - 2*(r-l+1)*(l-1);
    update(fenc, r+1, cc);

}
int get(int fen[], int id) {
    int res = 0;
    while(id > 0) {
        res += fen[id];
        id -= id &-id;
    }
    return res;
}
int sum(int id) {
    int a = get(fena, id);
    int b = get(fenb, id);
    int c = get(fenc, id);
    return a*id*id + b*id + c;
}

int Query(int l, int r) {
    return sum(r) - sum(l-1);
}
signed main() {
    ios_base::sync_with_stdio(false);cin.tie(0);
    cin >> n >> q;
    vector<int> a(n+5);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] += a[i-1];
    }

    while(q--) {
        int type, l, r;
        cin >> type >> l >> r;
        if(type == 1) {
            UpdateRange(l, r);
        } else {
            cout << Query(l, r) / 2 + a[r] - a[l - 1] << '\n';
        }
    }
    return 0-0 == 1;
}
