#include <bits/stdc++.h>
#define int long long
using namespace std;
struct Node {
    int val;
    Node *left, *right;
    Node (int val = 0, Node *left = nullptr, Node *right = nullptr) {
        this->val = val;
        this->left = left;
        this->right = right;
    }
};
struct PST {
    int n;
    vector<int> a;
    PST(int n = 0) : n(n), a(n + 1) {}
    Node *build(int l, int r) {
        if (l == r) {
            return new Node(a[l]);
        }
        int mid = (l + r) >> 1;
        Node *leftChild = build(l, mid);
        Node *rightChild = build(mid + 1, r);
        return new Node(leftChild->val + rightChild->val, leftChild, rightChild);
    }
    Node *update(Node *prev, int l, int r, int idx, int val) {
        if (l == r) {
            return new Node(val);
        }
        int mid = (l + r) >> 1;
        if (idx <= mid) {
            Node *newLeft = update(prev->left, l, mid, idx, val);
            return new Node(newLeft->val + prev->right->val, newLeft, prev->right);
        } else {
            Node *newRight = update(prev->right, mid + 1, r, idx, val);
            return new Node(prev->left->val + newRight->val, prev->left, newRight);
        }
    }
    int query(Node *node, int l, int r, int ql, int qr) {
        if (node == nullptr || l > qr || r < ql) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return node->val;
        }
        int mid = (l + r) >> 1;
        return query(node->left, l, mid, ql, qr) + query(node->right, mid + 1, r, ql, qr);
    }
};
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    PST st(n);
    for (int i = 1; i <= n; i++) {
        cin >> st.a[i];
    }
    Node *root = st.build(1, n);

    // Allocate enough space for all versions: initial + up to q new versions
    vector<Node *> pointer(q + 5, root);

    int p = 2;
    for (int i = 1; i <= q; i++) {
        int qt;
        cin >> qt;
        if (qt == 1) {
            int k, a, x; cin >> k >> a >> x;
            pointer[k] = st.update(pointer[k], 1, n, a, x);
        } else if (qt == 2) {
            int k, a, b; cin >> k >> a >> b;
            cout << st.query(pointer[k], 1, n, a, b) << '\n';
        } else {
            int k; cin >> k;
            pointer[p++] = pointer[k];
        }
    }
    return 0;
}
