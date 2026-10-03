#include <bits/stdc++.h>
#define int long long
using namespace std;
void solve() {
    int a, b;
    cin >> a >> b;
    
    if (a > b) swap(a, b);
    
    if(b > a * 2){
        cout << "NO" << endl;
    }
	else if(b * 2 == a){
        cout << "YES" << endl;
    }
	else if(a == b){
		if(a % 3 == 0){
			cout<<"YES"<<endl;
		}
		else{
			cout<<"NO"<<endl;
		}
	} else{
        if ((a - (b - a)) % 3 == 0) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        } 
	}

}
signed main() {
    int tc;
    cin >> tc;

    for (int t = 1; t <= tc; t++) {
        // cout << "Case " << t << ": ";
        solve();
    }
    return 0;
}