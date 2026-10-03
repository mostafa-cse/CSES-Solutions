#include <bits/stdc++.h>
using namespace std;

// Missing Coin Sum Queries (offline) using Fenwick tree and value buckets
// For each query [l, r], compute the smallest sum that cannot be formed
// from the multiset {a[l], ..., a[r]}.

struct Fenwick {
	int n;
	vector<long long> bit;

	Fenwick() : n(0) {}
	Fenwick(int n) : n(n), bit(n + 1, 0) {}

	void reset(int _n) {
		n = _n;
		bit.assign(n + 1, 0);
	}

	static inline int lb(int x) { return x & -x; }

	void add(int idx, long long val) {
		for (; idx <= n; idx += lb(idx)) bit[idx] += val;
	}

	long long sum(int idx) const {
		long long s = 0;
		for (; idx > 0; idx -= lb(idx)) s += bit[idx];
		return s;
	}

	long long rangeSum(int l, int r) const {
		if (l > r) return 0;
		return sum(r) - sum(l - 1);
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, q;
	if (!(cin >> n >> q)) return 0;

	vector<long long> a(n + 1);
	vector<long long> allVals;
	allVals.reserve(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		allVals.push_back(a[i]);
	}

	// Insert sentinel 1 to start from missing=1 logic
	allVals.push_back(1);
	sort(allVals.begin(), allVals.end());
	allVals.erase(unique(allVals.begin(), allVals.end()), allVals.end());

	// Map value -> index in allVals
	unordered_map<long long, int> id;
	id.reserve(allVals.size() * 2);
	for (int i = 0; i < (int)allVals.size(); i++) id[allVals[i]] = i;

	// Positions bucketed by value index
	vector<vector<int>> pos(allVals.size());
	for (int i = 1; i <= n; i++) pos[id[a[i]]].push_back(i);

	struct Query {
		int l, r;
	};

	vector<Query> qs(q + 1);
	for (int i = 1; i <= q; i++) {
		int l, r;
		cin >> l >> r;
		if (l > r) swap(l, r);
		qs[i] = {l, r};
	}

	// Buckets for queries: queries that should be evaluated after having added
	// all array values with value <= allVals[idx]. Start with idx=0 (sentinel 1)
	vector<vector<int>> buck(allVals.size());
	for (int i = 1; i <= q; i++) buck[0].push_back(i);

	Fenwick ft(n);
	vector<long long> answer(q + 1, 1);  // default minimal missing is 1

	for (int i = 0; i < (int)allVals.size(); i++) {
		// add all elements whose value equals allVals[i]
		for (int p : pos[i]) ft.add(p, a[p]);

		// process queries waiting at this threshold
		vector<int> nexts;
		nexts.reserve(buck[i].size());
		for (int qi : buck[i]) {
			auto [l, r] = qs[qi];
			long long v = ft.rangeSum(l, r);  // sum of values <= allVals[i] in [l,r]
			long long missing = v + 1;        // smallest not representable so far
			answer[qi] = missing;

			// If there exist more values <= missing, we need to move this query forward
			int pIdx = (int)(upper_bound(allVals.begin(), allVals.end(), missing) - allVals.begin()) - 1;
			if (pIdx > i) buck[pIdx].push_back(qi);  // continue later at a larger threshold
			// else stabilized at this answer
		}
		// free memory of processed bucket
		buck[i].clear();
		buck[i].shrink_to_fit();
	}

	for (int i = 1; i <= q; i++) cout << answer[i] << '\n';
	return 0;
}
