#include <bits/stdc++.h>
using namespace std;
#define int long long

// Matrix for affine transformations: f(x) = ax + b
// [a b] * [x] = [ax + b]
// [0 1]   [1]   [  1   ]
struct Matrix {
    int a[2][2];

    Matrix() {
        a[0][0] = 1; a[0][1] = 0;
        a[1][0] = 0; a[1][1] = 1;
    }

    Matrix(int a00, int a01, int a10, int a11) {
        a[0][0] = a00; a[0][1] = a01;
        a[1][0] = a10; a[1][1] = a11;
    }

    Matrix operator*(const Matrix& other) const {
        Matrix result;
        result.a[0][0] = a[0][0] * other.a[0][0] + a[0][1] * other.a[1][0];
        result.a[0][1] = a[0][0] * other.a[0][1] + a[0][1] * other.a[1][1];
        result.a[1][0] = a[1][0] * other.a[0][0] + a[1][1] * other.a[1][0];
        result.a[1][1] = a[1][0] * other.a[0][1] + a[1][1] * other.a[1][1];
        return result;
    }

    // Apply transformation: f(x) = a[0][0] * x + a[0][1]
    int apply(int x) const {
        return a[0][0] * x + a[0][1];
    }

    bool isIdentity() const {
        return a[0][0] == 1 && a[0][1] == 0 && a[1][0] == 0 && a[1][1] == 1;
    }
};

// Identity transformation: f(x) = x
Matrix identity() {
    return Matrix(1, 0, 0, 1);
}

// Add operation: f(x) = x + val
Matrix addOp(int val) {
    return Matrix(1, val, 0, 1);
}

// Set operation: f(x) = val
Matrix setOp(int val) {
    return Matrix(0, val, 0, 1);
}

struct Node {
    int sum;
    Matrix lazy;
    bool hasLazy;
    int len;

    Node() : sum(0), lazy(identity()), hasLazy(false), len(0) {}
};

class MatrixSegTree {
private:
    int n;
    vector<Node> tree;

    void push(int node, int start, int end) {
        if (!tree[node].hasLazy || tree[node].lazy.isIdentity()) return;

        // Apply transformation to sum
        if (tree[node].lazy.a[0][0] == 0) {
            // Set operation: all elements become the same value
            tree[node].sum = tree[node].lazy.a[0][1] * (end - start + 1);
        } else {
            // Add operation: f(x) = x + val, so sum becomes sum + val * length
            tree[node].sum += tree[node].lazy.a[0][1] * (end - start + 1);
        }

        // Push to children
        if (start != end) {
            // Compose transformations: new_lazy = old_lazy ∘ current_lazy
            tree[2*node].lazy = tree[node].lazy * tree[2*node].lazy;
            tree[2*node+1].lazy = tree[node].lazy * tree[2*node+1].lazy;
            tree[2*node].hasLazy = tree[2*node+1].hasLazy = true;
        }

        tree[node].lazy = identity();
        tree[node].hasLazy = false;
    }

    void build(int node, int start, int end, vector<int>& arr) {
        tree[node].len = end - start + 1;
        if (start == end) {
            tree[node].sum = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(2*node, start, mid, arr);
            build(2*node+1, mid+1, end, arr);
            tree[node].sum = tree[2*node].sum + tree[2*node+1].sum;
        }
    }

    void updateRange(int node, int start, int end, int l, int r, Matrix op) {
        if (start > r || end < l) return;

        if (start >= l && end <= r) {
            tree[node].lazy = op * tree[node].lazy;
            tree[node].hasLazy = true;
            push(node, start, end);
            return;
        }

        push(node, start, end);
        int mid = (start + end) / 2;
        updateRange(2*node, start, mid, l, r, op);
        updateRange(2*node+1, mid+1, end, l, r, op);

        push(2*node, start, mid);
        push(2*node+1, mid+1, end);
        tree[node].sum = tree[2*node].sum + tree[2*node+1].sum;
    }

    int queryRange(int node, int start, int end, int l, int r) {
        if (start > r || end < l) return 0;

        push(node, start, end);
        if (start >= l && end <= r) {
            return tree[node].sum;
        }

        int mid = (start + end) / 2;
        return queryRange(2*node, start, mid, l, r) +
               queryRange(2*node+1, mid+1, end, l, r);
    }

public:
    MatrixSegTree(vector<int>& arr) {
        n = arr.size() - 1;
        tree.resize(4 * n + 1);
        build(1, 1, n, arr);
    }

    void rangeAdd(int l, int r, int val) {
        updateRange(1, 1, n, l, r, addOp(val));
    }

    void rangeSet(int l, int r, int val) {
        updateRange(1, 1, n, l, r, setOp(val));
    }

    int rangeSum(int l, int r) {
        return queryRange(1, 1, n, l, r);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    MatrixSegTree seg(a);

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) { // range add
            int l, r, x;
            cin >> l >> r >> x;
            seg.rangeAdd(l, r, x);
        } else if (type == 2) { // range set
            int l, r, x;
            cin >> l >> r >> x;
            seg.rangeSet(l, r, x);
        } else { // range sum query
            int l, r;
            cin >> l >> r;
            cout << seg.rangeSum(l, r) << "\n";
        }
    }

    return 0;
}

/*
MATRIX EXPONENTIATION TECHNIQUE EXPLANATION:

1. AFFINE TRANSFORMATIONS:
   - Every operation can be represented as f(x) = ax + b
   - Add operation: f(x) = 1·x + val  (matrix: [1 val; 0 1])
   - Set operation: f(x) = 0·x + val  (matrix: [0 val; 0 1])

2. COMPOSITION OF OPERATIONS:
   - Matrix multiplication represents function composition
   - If we have f₁(x) = a₁x + b₁ and f₂(x) = a₂x + b₂
   - Then f₁(f₂(x)) = a₁(a₂x + b₂) + b₁ = (a₁a₂)x + (a₁b₂ + b₁)
   - Matrix: [a₁ b₁] * [a₂ b₂] = [a₁a₂  a₁b₂+b₁]
            [0  1 ]   [0  1 ]   [0     1      ]

3. LAZY PROPAGATION WITH MATRICES:
   - Each node stores a transformation matrix
   - When updating, compose the new operation with existing lazy matrix
   - When pushing, apply the transformation to children

4. SUM CALCULATION:
   - For add operation f(x) = x + val on range [l,r]:
     sum becomes original_sum + val × length
   - For set operation f(x) = val on range [l,r]:
     sum becomes val × length

5. ADVANTAGES:
   - Unified representation of all operations
   - Natural composition through matrix multiplication
   - Mathematically elegant and extensible

This approach uses matrix exponentiation principles (composition of linear transformations)
to solve the range update/sum problem efficiently in O(log n) per operation.
*/
