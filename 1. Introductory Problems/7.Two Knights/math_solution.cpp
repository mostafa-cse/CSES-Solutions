/*
all Formula:
    For First Knight Move = i * i
    for Second knight Moves = (i * i) - 1
    For K Knights Moves = (i * i)Ck
 
    for 2knights Move = (i*i)C2 = i * i * (i * i - 1) / 2
    Attacking Move = 2[horizontal 2x3 grid] * 2[vertical 2x3 grid] * (i - 1) * (i - 2)
 
    ans = i^2 * (i^2 - 1) / 2 - 4 * (i - 1) * (i - 2)
*/
#include<bits/stdc++.h>
#define int long long
using namespace std;

int32_t main() {
    int n;
    cin >> n;
 
    for (int i = 1; i <= n; ++i) {
        int total = pow(i, 2) * (pow(i, 2) - 1) / 2;
        int attacking = 4 * (i - 1) * (i - 2);
 
        cout << total - attacking << endl;
    }
    return 0;
}