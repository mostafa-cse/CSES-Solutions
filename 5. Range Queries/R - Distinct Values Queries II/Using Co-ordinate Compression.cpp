#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

tuple<int,int,int> qs[N];
int a[N], sg[N << 2], b[N];

void build(int idx, int L, int R){
    if(L == R) return sg[idx] = b[L], void();
    int m = (L + R) / 2;
    build(idx * 2, L, m);
    build(idx * 2 + 1, m + 1, R);
    sg[idx] = max(sg[idx * 2], sg[idx * 2 + 1]);
}

int query(int idx, int L, int R, int p, int q){
    if(p <= L && R <= q) return sg[idx];
    if(q < L || R < p) return -1;
    int m = (L + R) / 2;
    return max(query(idx * 2, L, m, p, q),
               query(idx * 2 + 1, m + 1, R, p, q));
}

void update(int idx, int L, int R, int p, int q){
    if(L == R) return sg[idx] = q, void();
    int m = (L + R) / 2;
    if(p <= m) update(idx * 2, L, m, p, q);
    else update(idx * 2 + 1, m + 1, R, p, q);
    sg[idx] = max(sg[idx * 2], sg[idx * 2 + 1]);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    set<int> num;
    unordered_map<int,int> compress;
    vector<int> num2;

    int n, qu;
    cin >> n >> qu;
    for(int i = 1; i <= n; ++i){
        cin >> a[i];
        num.insert(a[i]);
    }

    int p, q, r;
    for(int i = 1; i <= qu; ++i){
        cin >> p >> q >> r;
        qs[i] = {p, q, r};
        if(p == 1) num.insert(r);
    }

    vector< set<int> > pos(num.size() + 5);
    num2.push_back(-1);
    int cnt = 1;
    for(auto v : num){
        pos[cnt].insert(-1);
        compress[v] = cnt;
        num2.push_back(v);
        ++cnt;
    }

    for(int i = 1; i <= n; ++i){
        a[i] = int(lower_bound(num2.begin(), num2.end(), a[i]) - num2.begin());
        b[i] = *pos[a[i]].rbegin();
        pos[a[i]].insert(i);
    }

    build(1, 1, n);

    // Iterators for the sets in pos
    set<int>::iterator it, after, before, last;

    for(int i = 1; i <= qu; ++i){
        tie(p, q, r) = qs[i];
        if(p == 1){
            int idx = q;
            int val = r;
            val = int(lower_bound(num2.begin(), num2.end(), val) - num2.begin());

            it = pos[a[idx]].find(idx);
            last = pos[a[idx]].end(); --last;
            if(it != last){
                after = before = it;
                ++after, --before;
                update(1, 1, n, *after, *before);
            }
            pos[a[idx]].erase(it);


            a[idx] = r;
            pos[a[idx]].insert(idx);
            it = pos[a[idx]].find(idx);
            last = pos[a[q]].end(); --last;
            if(it != last){
                after = it; ++after;
                update(1, 1, n, *after, *it);
            }
            before = it; --before;
            update(1, 1, n, *it, *before);
        }else{
            puts(query(1, 1, n, q, r) < q ? "YES" : "NO");
        }
    }
    return 0;
}
