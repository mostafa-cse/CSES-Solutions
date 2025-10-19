/*
* one more solution :
* https://cses.fi/problemset/hack/2134/entry/1501751/
* https://cses.fi/problemset/hack/2134/entry/1781649/
* https://cses.fi/problemset/hack/2134/entry/1779314/
* https://cses.fi/problemset/hack/2134/entry/1741057/
*/
#include <bits/stdc++.h>
using namespace std;

struct linkcut {

  linkcut *par, *left, *right;
  long long value, maxi, sum;
  bool flip;

  linkcut() {
    par = left = right = nullptr;
    flip = false;
  }

};

bool root(linkcut *u) {
  return !u->par || (u->par->left != u && u->par->right != u);
}

bool left(linkcut *u) {
  return u == u->par->left;
}

long long sum(linkcut *u) {
  return u ? u->sum : 0;
}

long long maxi(linkcut *u) {
  return u ? u->maxi : 0;
}

void pull(linkcut *u) {
  u->sum = sum(u->left) + u->value + sum(u->right);
  u->maxi = max({maxi(u->left), u->value, maxi(u->right)});
}

void push(linkcut *u) {
  if (!u || !u->flip) {
    return;
  }

  u->flip = false;
  swap(u->left, u->right);
  if (u->left) {
    u->left->flip ^= true;
  }
  if (u->right) {
    u->right->flip ^= true;
  }
}

void assign(linkcut *u, linkcut *v, bool d) {
  (d ? u->left : u->right) = v;
  if (v) {
    v->par = u;
  }
}

void rotate(linkcut *u) {
  linkcut *p = u->par, *g = p->par;
  bool d = left(u);
  assign(p, d ? u->right : u->left, d);
  if (!root(p)) {
    assign(g, u, left(p));
  } else {
    u->par = g;
  }
  assign(u, p, !d);
  pull(p), pull(u);
}

void splay(linkcut *u) {
  while (!root(u)) {
    linkcut *p = u->par;
    push(p->par), push(p), push(u);
    if (!root(p)) {
      rotate((left(u) == left(p)) ? p : u);
    }
    rotate(u);
  }
  push(u);
}

void access(linkcut *u) {
  linkcut *c = nullptr;
  for (linkcut *v = u; v; v = v->par) {
    splay(v);
    v->right = c;
    pull(v);
    c = v;
  }
  splay(u);
}

void reroot(linkcut *u) {
  access(u);
  u->flip ^= true;
}

void link(linkcut *u, linkcut *v) {
  reroot(v), access(u);
  v->par = u;
}

void cut(linkcut *u, linkcut *v) {
  reroot(v), access(u);
  u->left->par = nullptr;
  u->left = nullptr;
}

const int N = 200000 + 1;

linkcut *tree[N];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  for (int i = 1; i <= n; ++i) {
    int v;
    cin >> v;
    tree[i] = new linkcut();
    tree[i]->value = v;
  }

  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    cin >> u >> v;
    link(tree[u], tree[v]);
  }

  while (q--) {
    int t;
    cin >> t;

    if (t == 1) {
      int s, x;
      cin >> s >> x;
      access(tree[s]);
      tree[s]->value = x;
      pull(tree[s]);
    } else {
      int a, b;
      cin >> a >> b;
      reroot(tree[a]), access(tree[b]);
      cout << maxi(tree[b]) << " ";
    }
  }
  cout << "\n";
}
