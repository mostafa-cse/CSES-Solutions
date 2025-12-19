#include<bits/stdc++.h>
#define int long long
using namespace std;

const int INF=1e9;
const int INFI=1e15;
struct Suffix_Tree {
    struct Node {
        int l, r, par, link;
        int next[26];
        Node(int _l=0, int _r=0, int _p=-1)
          : l(_l), r(_r), par(_p), link(-1)
        {
            memset(next, -1, sizeof(next));
        }
        int len() const { return r - l; }
    };

    string S;
    vector<Node> st;
    struct State { int v, pos; };
    State ptr;

    Suffix_Tree(const string& s) : S(s), st(), ptr{0,0} {
        int n = S.size();
        st.reserve(2*n);
        st.emplace_back(0, 0, -1);  // root
        build();
    }

    bool contains(const string& pat) const {
        int v = 0, pos = 0, i = 0, m = pat.size();
        while (i < m) {
            auto &node = st[v];
            if (pos == node.len()) {
                int c = pat[i] - 'a';
                int to = node.next[c];
                if (to < 0) return false;
                v = to;
                pos = 0;
            }
            if (S[st[v].l + pos] != pat[i])
                return false;
            ++pos; ++i;
        }
        return true;
    }

private:
    State go(State s, int l, int r) {
        while (l < r) {
            auto &node = st[s.v];
            if (s.pos == node.len()) {
                int c = S[l] - 'a';
                s.v   = node.next[c];
                s.pos = 0;
                if (s.v < 0) return {-1,-1};
            } else {
                if (S[node.l + s.pos] != S[l])
                    return {-1,-1};
                int edge_rem = node.len() - s.pos;
                if (r - l < edge_rem) {
                    s.pos += (r - l);
                    return s;
                }
                l    += edge_rem;
                s.pos = node.len();
            }
        }
        return s;
    }

    int split(State s) {
        auto &node = st[s.v];
        if (s.pos == node.len()) return s.v;
        if (s.pos == 0)          return node.par;

        Node copy = node;
        int mid = st.size();
        st.emplace_back(copy.l, copy.l + s.pos, copy.par);
        st[ copy.par ].next[ S[copy.l] - 'a' ] = mid;
        st[ mid ].next[ S[copy.l + s.pos] - 'a' ] = s.v;

        node.par = mid;
        node.l  += s.pos;
        return mid;
    }

    int get_link(int v) {
        if (st[v].link != -1) return st[v].link;
        if (st[v].par == -1) return 0;
        int to = get_link(st[v].par);
        State ss{ to, st[to].len() };
        st[v].link = split(go(ss,
                              st[v].l + (st[v].par == 0),
                              st[v].r));
        return st[v].link;
    }

    void build() {
        int n = S.size();
        for (int i = 0; i < n; ++i) {
            for (;;) {
                State np = go(ptr, i, i+1);
                if (np.v != -1) {
                    ptr = np;
                    break;
                }
                int mid = split(ptr);
                int leaf = st.size();
                st.emplace_back(i, n, mid);
                st[mid].next[S[i] - 'a'] = leaf;
                ptr.v = get_link(mid);
                ptr.pos = st[ptr.v].len();
                if (mid == 0) {
                    break;
                }
            }
        }
    }
};

int32_t main(){
    string s;
    cin >> s;

    Suffix_Tree st(s);

    int q;
    cin >> q;
    while(q--){
        string p;
        cin >> p;

        cout << (st.contains(p) ? "YES" : "NO") << endl;
   }
    return 0;
}
