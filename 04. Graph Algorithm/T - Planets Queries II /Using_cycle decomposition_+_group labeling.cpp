#include <bits/stdc++.h>
using namespace std;
#define all(x) x.begin(), x.end()

const int max_n = 2e5 + 1;
int next_a[max_n];
int groups[max_n];
int group_types[max_n];
int next_g[max_n];
int lenght[max_n];
int order[max_n];

struct pair_hash
{
	template <class T1, class T2>
	std::size_t operator() (const std::pair<T1, T2>& pair) const {
		return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	int n, q;
	cin >> n >> q;
    vector<int> in(n + 1);

    for (int i = 1; i <= n; i++)
	{
        cin >> next_a[i];
        in[i] = i;
	}
    // Why it is so Important?
	std::random_device rd;
	std::mt19937 g(rd());
	shuffle(all(in), g);
 
	int current_group = 1;
 
	for (int i = 0; i <= n; i++)
	{
		if (in[i] == 0 || groups[in[i]]) continue;
 
		int p = in[i];
		int orderr = 0;
		int used = 0;
 
		while (!groups[p]) {
			used++;
			groups[p] = current_group;
			order[p] = orderr++;
			p = next_a[p];
		}
 
		int l = current_group;
		bool lo = false;
		if (groups[p] == current_group) {
			lo = true;
			if (used >= 2)
				current_group++;
 
			int orderr = 0;
			int current = p;
			do {
				order[current] = orderr++;
				groups[current] = current_group;
				current = next_a[current];
			} while (p != current);
			lenght[current_group] = orderr;
 
			group_types[current_group] = 1;
		}
		next_g[l] = p;
		p = in[i];
 
		lenght[l] = orderr;
		if (lo) lenght[l] -= lenght[current_group];
		
 
		current_group++;
	}
 
 
 
	int dist = 0;
    unordered_map<pair<int, int>, int, pair_hash> m;
    unordered_map<pair<int, int>, int, pair_hash>::iterator it;

    while (q--) {
		int a, b;
        cin >> a >> b;

        if(dist < 10)
		it = m.find({ a,b });
 
		int d = 0;
		int ans = -1;
		if (dist < 10 && it != m.end()) { ans = it->second; }
		else dist++;
 
		if (a == b) { ans = 0; }
 
		if (ans == -1) {
			while (groups[a] != groups[b] && group_types[groups[a]] != 1) {
				d += lenght[groups[a]] - order[a];
				a = next_g[groups[a]];
			}
 
			if (groups[a] == groups[b]) {
 
				if (group_types[groups[a]]) { // a , b - loop 
 
					if (order[a] > order[b])
						ans = lenght[groups[a]] - order[a] + order[b] + d;
					else
						ans = order[b] - order[a] + d;
 
				}
				else
					if (order[a] <= order[b])
						ans = order[b] - order[a] + d;
 
			}
		}
 
		if(dist < 10)
		m[{a, b}] = ans;
 
		if (ans == -1) {
			cout << ('-');
			cout << ('1');
		}
		else {
            cout << (ans);
        }
		cout << ('\n');
 
	}
}