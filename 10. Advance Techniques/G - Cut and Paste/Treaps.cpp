#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
inline int gen_random(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

struct Node {
    int key, priori;
    int size;
    Node *left, *right;
    Node() {
        size = 0;
        left = right = nullptr;
    }
    Node(int k, int p) : size(1), key(k), priori(p), left(NULL), right(NULL) {}
};
struct Treap {
    Node *root = nullptr;
    int size(Node *t) {
        if (t != nullptr) {
            return t->size;
        }
        return 0;
    }
    void update(Node *t) {
        if (t == nullptr) return;
        t->size = 1 + size(t->left) + size(t->right);
    }
    void split(Node *t, int len, Node *&a, Node *&b) {
        if (t == nullptr) {
            a = b = nullptr;
            return;
        }
        if (size(t->left) >= len) {
            split(t->left, len, a, t->left);
            b = t;
            update(b);
        } else {
            split(t->right, len - size(t->left) - 1, t->right, b);
            a = t;
            update(a);
        }
    }
    Node* merge(Node* a, Node* b) {
        if (a == nullptr or b == nullptr) {
            if (a != nullptr) {
                return a;
            }
            return b;
        }
        if (a->priori > b->priori) {
            a->right = merge(a->right, b);
            update(a);
            return a;
        } else {
            b->left = merge(a, b->left);
            update(b);
            return b;
        }
    }
    void build(const string& s) {
        for (char c : s) {
            root = merge(root, new Node((int)c, gen_random(0, s.size())));
        }
    }
    void print(Node *root) {
        if (root == nullptr) {
            return;
        }
        print(root->left);
        cout << char(root->key);
        print(root->right);
    }
    Node* cut_AddToEnd(int l, int r) {
        Node *t1, *t2, *t3, *mid;
        t1 = t2 = t3 = mid = nullptr;

        //t1 = [1....l-1], t2 =[l....n]
        split(root, l - 1, t1, t2);

        // mid=[a...b], t3 = [b + 1.....n]
        split(t2, r - l + 1, mid, t3);

        root = merge(t1, t3);
        root = merge(root, mid);
        return root;
    }
};
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    Treap treap;
    treap.build(s);

    while (k--) {
        int l, r;
        cin >> l >> r;
        treap.root = treap.cut_AddToEnd(l, r);
    }
    treap.print(treap.root);
    return 0;
}
