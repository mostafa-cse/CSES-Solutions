#include <bits/stdc++.h>
#define int long long
using namespace std;
int expo (int a, int p){
    int res = 1;
    while (p) {
        if(p & 1) {
            res = (a * res);
        }
        p >>= 1;
        a = (a * a);
    }
    return res;
}
signed main() {
    for (int i = 1; i <= 100000; i++) {
        int left = 1 << i;
        int right = expo(i, 32);

        if (left == right) {
            cout << i << endl;
            break;
        }
    }

}