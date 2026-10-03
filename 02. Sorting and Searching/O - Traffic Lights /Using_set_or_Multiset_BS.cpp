#include<bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);  cout.tie(0);
    int Len, n;
    cin >> Len >> n;

    int ans = 0;
    multiset<int> Lights = {0, Len}, dist = {Len};
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        auto it = Lights.upper_bound(x);
        auto pore = it;
        auto age = --it;
        
        dist.erase(dist.find(*pore - *age));
        dist.insert(x - *age);
        dist.insert(*pore - x);

        Lights.insert(x);

        it = dist.end();
        cout << *prev(it) << " ";
    }
    return 0;
}
