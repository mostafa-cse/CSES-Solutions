#include <bits/stdc++.h>
using namespace std;
#define int long long
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
const int N = 2e5 + 5;
vector<int> pre;
int getSum(int l, int r) {
    if (l > r) return 0;
    return pre[r] - (l == 0 ? 0 : pre[l - 1]);
}

class SegmentTree {
private:
    int n;
    const pair<int, int> zero = {0, -1};
    vector<int> &nums;
    vector<int> &right;
    vector<pair<int, int>> node;

    pair<int, int> merge(pair<int, int> a, pair<int, int> b) {
        if (a == zero || b == zero) return (a != zero ? a : b);
        // pick index with larger nums value
        int cost = a.first + b.first;
        int big = (nums[a.second] > nums[b.second] ? a.second : b.second);
        return {cost, big};
    }

    pair<int, int> query(int l, int r, int L, int R, int head) {
        if (l > R || L > r) return zero;
        if (L <= l && r <= R) return node[head];

        int mid = (l + r) >> 1;
        pair<int, int> lhs = query(l, mid, L, R, head * 2 + 1);
        pair<int, int> rhs = query(mid + 1, r, L, R, head * 2 + 2);
        return merge(lhs, rhs);
    }

    void build(int l, int r, int head) {
        if (l == r) {

            int id = right[l] - 1; //back to previous
            int len = id - l; // length of subarray that can convert a[i] to a[l]

            int preCost = query(l + 1, id).first;
            node[head] = {nums[l] * len - getSum(l + 1, id) - preCost, l};
            return;
        }
        int mid = (l + r) >> 1;
        build(mid + 1, r, head * 2 + 2);
        build(l, mid, head * 2 + 1);
        node[head] = merge(node[head * 2 + 1], node[head * 2 + 2]);
    }

public:
    SegmentTree(vector<int> &_nums, vector<int> &_right) : nums(_nums), right(_right) {
        n = (int)nums.size() - 1;
        int m = 1; while (m < 2 * n) m <<= 1;
        node.assign(m, zero);
        build(0, n - 1, 0);
    }

    pair<int, int> query(int l, int r) {
        if (l > r) return zero;
        return query(0, n - 1, l, r, 0);
    }
};

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<int> nums(n + 1);
    nums[n] = (int)2e9 + 10;
    for (int i = 0; i < n; i++) cin >> nums[i];

    pre = nums;
    for (int i = 1; i < n; i++) pre[i] += pre[i - 1];

    vector<int> right(n, -1);
    vector<int> stk; stk.push_back(n);
    for (int i = n - 1; i >= 0; i--) {
        while (nums[stk.back()] <= nums[i]) stk.pop_back();
        right[i] = stk.back();
        stk.push_back(i);
    }

    SegmentTree seg(nums, right);

    for (int _ = 0; _ < q; _++) {
        int l, r;
        cin >> l >> r;
        l--, r--;

        int mid = seg.query(l, r).second;
        // big value idx mid between [l, r]

        int ans = 0;
        if (mid > l) ans = max(0ll, seg.query(l, mid - 1).first);

        int bigVal = nums[mid];

        ans += (r - mid + 1) * bigVal - getSum(mid, r);

        cout << ans << '\n';
    }
    return 0;
}
