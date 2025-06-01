#include <bits/stdc++.h>
using namespace std;
int n, m, ptr, x[500], sum;
vector<string> c(8);
vector <int> v;
int Rec (int x) {
	if (x == 8) {
		sum++;
		return;
	}

    int ans = 0;
    for (int i = 0; i < 8; i++) {
		if (c[x][i] != '*') {
			bool b = true;
			for (int j = 0; j < x and b; j++) {
				if (v[j] == i || abs (x - j) == abs (v[j] - i)) {
                    b = false;
                }
			}
 
			if (b) {
				v.push_back (i);
                ans += Rec(x + 1);
                v.pop_back ();
			}
		}
	}
    return ans;
}
 
int main () {
	for (int i = 0; i < 8; i++) {
        cin >> c[i];
    }
	cout << Rec (0);
    return 0;
}