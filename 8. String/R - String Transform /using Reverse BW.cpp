#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()

string reverseBW(string t) {
    int n = t.size();

    vector<int> nex(n);
    iota(all(nex), 0);

    stable_sort(all(nex), [&t](int a, int b) {
        return t[a] < t[b];
    });
    string s;
    for (int i = nex[0]; i;) {
        s += t[i = nex[i]];
    }
    return s;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string t;
	if (cin >> t) {
		cout << reverseBW(t) << '\n';
	}
	return 0;
}
