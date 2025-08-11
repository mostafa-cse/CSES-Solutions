#include <bits/stdc++.h>
using namespace std;

struct BIT {
    int n;
    vector<long long> bit;
    BIT(int n) : n(n), bit(n + 1, 0) {}
    
    void add(int idx, long long val) {
        for (; idx <= n; idx += idx & -idx)
            bit[idx] += val;
    }
    
    long long sum(int idx) {
        long long res = 0;
        for (; idx > 0; idx -= idx & -idx)
            res += bit[idx];
        return res;
    }
};

struct RangeBIT {
    int n;
    BIT B1, B2;
    RangeBIT(int n) : n(n), B1(n), B2(n) {}

    void range_add(int l, int r, long long val) {
        B1.add(l, val);
        B1.add(r + 1, -val);
        B2.add(l, val * (l - 1));
        B2.add(r + 1, -val * r);
    }

    long long prefix_sum(int x) {
        return B1.sum(x) * x - B2.sum(x);
    }

    long long range_sum(int l, int r) {
        return prefix_sum(r) - prefix_sum(l - 1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
	int n, q;
	cin >> n >> q;

    RangeBIT bit(n + 1);
    for (int i = 1; i <= n; i++) {
    	int x;
    	cin >> x;
    	bit.range_add(i, i, x);
    }
    
    while (q--) {
    	int qt;
    	cin >> qt;

    	if (qt & 1) {
    		int l, r, val;
    		cin >> l >> r >> val;
    		bit.range_add(l, r, val);
    	} else {
    		int x;
    		cin >> x;

    		cout << bit.range_sum(x, x) << endl;
    	}
    }
    return 0;
}