#include<bits/stdc++.h>
#define int long long
using namespace std;
struct segment_tree {
	int n;
    vector<int> assign, add, tree, a;
    vector<bool> pending;
	segment_tree(int n) {
		tree.assign(4 * n + 1, 0);
		assign.assign(4 * n + 1, 0);
		add.assign(4 * n + 1, 0);
		pending.assign(4 * n + 1, false);
        a.resize(n + 1);
	}
	void propagate(int node, int l, int r) {
		int len = (r - l + 1);
		if (pending[node]) {
			tree[node] = len * assign[node];
			if (l != r) {
				assign[node << 1] = assign[node];
				assign[node << 1 | 1] = assign[node];
				pending[node << 1] = 1;
				pending[node << 1 | 1] = 1;

				add[node << 1] = 0;
				add[node << 1 | 1] = 0;
			}
		} else {
			tree[node] += len * add[node];
			if (l != r) {
				if (pending[node << 1]) { // left
					assign[node << 1] += add[node];
				} else {
					add[node << 1] += add[node];
				}

				if (pending[node << 1 | 1]){ // right
					assign[node << 1 | 1] += add[node];
				} else {
					add[node << 1 | 1] += add[node];
				}
			}
		}
		pending[node] = 0;
		assign[node] = 0;
		add[node] = 0;
	}
     void build(int node, int start, int end){
        if (start == end) {
            tree[node] = a[start];
            return;
        }
        int mid = start + (end - start) / 2;
        build(node * 2, start, mid);
        build(node * 2 + 1, mid + 1, end);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
	void Update_assign(int node, int l, int r, int ql, int qr, int val) {
		propagate(node, l, r);
		if (l > qr or r < ql) {
			return;
		} else if (l >= ql and r <= qr) {
			assign[node] = val;
			add[node] = 0;
			pending[node] = 1;
			propagate(node, l, r);
		} else {
			int mid = (l + r) >> 1;
			Update_assign(node << 1, l, mid, ql, qr, val);
			Update_assign(node << 1 | 1, mid + 1, r, ql, qr, val);
			tree[node] = tree[node << 1] + tree[node << 1 | 1];
		}
	}
	void Update_add(int node, int l, int r, int ql, int qr, int val) {
		propagate(node, l, r);
		if (l > qr or r < ql) {
			return;
		} else if (l >= ql and r <= qr) {
			if (pending[node]) {
				assign[node] += val;
			} else {
				add[node] += val;
			}
			propagate(node, l, r);
		} else {
			int mid = (l + r) >> 1;
			Update_add(node << 1, l, mid, ql, qr, val);
			Update_add(node << 1 | 1, mid + 1, r, ql, qr, val);
			tree[node] = tree[node << 1] + tree[node << 1 | 1];
		}
	}
	int query(int node, int l, int r, int ql, int qr) {
		propagate(node, l, r);
		if (l > qr or r < ql) {
			return 0;
		} else if (l >= ql and r <= qr) {
			return tree[node];
		} else {
			int mid = (l + r)  >> 1;
			int left = query(node << 1, l, mid, ql, qr);
			int right = query(node << 1 | 1, mid + 1, r, ql, qr);
			return left + right;
		}
	}
};
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);  cout.tie(0);
    int n, q;
    cin >> n >> q;

    segment_tree a(n);
    for (int i = 1; i <= n; ++i) {
        cin >> a.a[i];
    }
    a.build(1, 1, n);

    while (q--) {
    	int op, l, r, v;
    	cin >> op >> l >> r;

    	if (op <= 2) {
    		cin >> v;

    		if (op & 1) {
                a.Update_add(1, 1, n, l, r, v);
    		} else {
                a.Update_assign(1, 1, n, l, r, v);
            }
    	} else {
            cout << a.query(1, 1, n, l, r) << endl;
        }
    }
    return 0;
}
