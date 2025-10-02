#include <bits/stdc++.h>
#define int long long
using namespace std;

struct Node{
  int maxVal; // maximum element in this segment
  int sum;    // sum of elements in this segment
  int cost;   // cost to make this segment non-decreasing
};

const int MAXN = 200005;
Node tree[MAXN * 4];
int arr[MAXN];
Node merge(int start, int end, int node) {
    int mx = arr[start], sum = arr[start], cost = 0;
    for (int i = start + 1; i <= end; i++){
        if (arr[i] >= mx) {
            mx = arr[i];
        } else{
            cost += (mx - arr[i]);
        }
        sum += arr[i];
    }
    return {mx, sum, cost};
}
// Build the segment tree
void build(int node, int start, int end){
    if (start == end){
        tree[node] = { arr[start], arr[start], 0 };
        return;
    }
    int mid = (start + end) / 2;
    build(node * 2, start, mid);
    build(node * 2 + 1, mid + 1, end);
    tree[node] = merge(start, end, node);
}
// #define cost first
// #define mx second
// Walk inside a segment and calculate operations
pair<int, int> walk(int node, int start, int end, int mx){
    if (start == end) {
        if (arr[start] >= mx) {
            return {0, arr[start]};
        } else {
            return {mx - arr[start], mx};
        }
    }
    if (tree[node].maxVal <= mx){
        return { mx * (end - start + 1) - tree[node].sum, mx };
    }

    int mid = (start + end) / 2;
    if (tree[node * 2].maxVal >= mx) {
        int rightCost = tree[node].cost - tree[node * 2].cost;
        auto left = walk(node * 2, start, mid, mx);
        return {left.first + rightCost, tree[node].maxVal};
    } else {
        auto right = walk(node * 2 + 1, mid + 1, end, mx);
        return {right.first + mx * (mid - start + 1) - tree[node * 2].sum, tree[node].maxVal};
    }
}

// Query on [L, R]
pair<int, int> query(int node, int start, int end, int L, int R, int mx){
    if (start > R || end < L) return {0, mx};

    if (start >= L && end <= R) {
        return walk(node, start, end, mx);
    }

    int mid = (start + end) / 2;
    auto left = query(node * 2, start, mid, L, R, mx);
    auto right = query(node * 2 + 1, mid + 1, end, L, R, left.second);
    return {left.first + right.first, right.second};
}

signed main(){
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    build(1, 1, n);

    while (q--){
      int l, r;
      cin >> l >> r;
      cout << query(1, 1, n, l, r, 0).first << "\n";
    }
    return 0;
}
