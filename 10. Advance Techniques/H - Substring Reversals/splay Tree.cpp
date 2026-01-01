#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
long long random(long long l, long long r) {
    return uniform_int_distribution<long long>(l, r)(rng);
}
unsigned long long random(unsigned long long l, unsigned long long r) {
    return uniform_int_distribution<unsigned long long>(l, r)(rng);
}
template <class T> T random(T r) {
    return rng() % r;
}

const int N = 1e6 + 5;
const int MOD = 1e9 + 7;
const int inf = 1e9;
const long long INF = 1e18;

int n, m;

struct Node {
    Node *parent, *child[2];
    int sz; char key;
    bool reverse;

    Node(char ch = 'A') {
        parent = child[0] = child[1] = nullptr;
        sz = 1, key = ch, reverse = false;
    }

    int side() {
        return parent ? parent->child[1] == this : -1;
    }

    void pushDown() {
        if (reverse) {
            swap(child[0], child[1]);
            if (child[0]) child[0]->reverse ^= 1;
            if (child[1]) child[1]->reverse ^= 1;
            reverse = false;
        }
    }

    void pushUp() {
        sz = 1;
        if (child[0]) sz += child[0]->sz;
        if (child[1]) sz += child[1]->sz;
    }
};
const int NUM_NODES = 2e5 + 5;
Node nodes[NUM_NODES];
int numNode = 0;

Node *newNode(char ch) {
    nodes[numNode] = Node(ch);
    return &nodes[numNode++];
}

struct SplayTree {
    Node *root;

    SplayTree() {
        root = newNode('A');
        link(root, newNode('Z'), 1);
        root->pushUp();
    }

    void link(Node *a, Node *b, int dir) {
        if (!a) {
            root = b;
            if (root) root->parent = nullptr;
            return;
        }
        a->child[dir] = b;
        if (b) b->parent = a;
    }

    void rotate(Node *a) {
        // cerr << "rotate " << '\n';
        Node *p = a->parent;
        int dir = a->side();

        link(p->parent, a, p->side());
        link(p, a->child[!dir], dir);
        link(a, p, !dir);
        p->pushUp(), a->pushUp();
    }

    void splay(Node *a, Node *s = nullptr) {
        while (a->parent != s) {
            Node *p = a->parent;

            if (p->parent == s) rotate(a);
            else if (a->side() == p->side()) rotate(p), rotate(a);
            else rotate(a), rotate(a);
        }
    }

    void find(int k, Node *s = nullptr) {
        Node *p = root;
        while (true) {
            p->pushDown();
            int cntLeft = (p->child[0] ? p->child[0]->sz : 0);

            if (cntLeft > k) p = p->child[0];
            else if (cntLeft + 1 > k) {
                splay(p, s); return;
            }
            else k -= cntLeft + 1, p = p->child[1];
        }
    }

    // root->child[0]->child[1] = (l, r)
    void splay(int l, int r) {
        find(r + 1);
        find(l - 1, root);
    }

    void insert(int k, char ch) {
        splay(k, k - 1);
        // cerr << "sigma " << root->key << '\n';
        link(root->child[0], newNode(ch), 1);
        // cerr << "alo\n";
        root->child[0]->pushUp(), root->pushUp();
    }

    void flip(int l, int r) {
        splay(l, r);
        // cerr << root->key << '\n';
        // cerr << root->child[0]->key << '\n';
        assert(root->child[0]->child[1]);
        root->child[0]->child[1]->reverse ^= 1;
    }

    char get(int k) {
        find(k);
        return root->key;
    }
} tree;

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        char ch; cin >> ch;
        tree.insert(i, ch);
    }

    // tree.flip(1, 2);
    for (int i = 1; i <= m; ++i) {
        int l, r; cin >> l >> r;
        tree.flip(l, r);
    }

    for (int i = 1; i <= n; ++i) cout << tree.get(i);
    return 0;
}

