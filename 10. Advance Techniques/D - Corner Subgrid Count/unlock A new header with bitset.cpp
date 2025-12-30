#include<bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
bitset<3005> b[3005];
int main(){
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char c;
            cin >> c;
            b[i][j] = c - '0';
        }
    }

    long long ans = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++){
            long long m = (b[i] & b[j]).count();
            ans += m * (m - 1) / 2;
        }
    }
    cout << ans << endl;
    return 0;
}
