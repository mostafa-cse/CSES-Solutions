
#include <bits/stdc++.h>
using namespace std;
#define starburst ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
typedef long long ll;
//#define int ll
#define vi vector<int>
#define pii pair<int,int>
#define mii map<int,int>
#define si stack<int>
#define qi queue<int>
#define upb upper_bound
#define lwb lower_bound
#define pf push_front
#define pb push_back
#define pp push
#define pof pop_front
#define pob pop_back
#define ff first
#define ss second
#define inf 1000000007
#define mod 998244353
#define modd inf
#define N 200005
#define gcd __gcd
#define skip(x) if(x)continue;

int n, m, tmp = 0, r = 0;
ll a[N], ans[N];

struct qry{
    int l, r, t;
    qry(int li, int ri, int ti):l(li), r(ri), t(ti){}
};

bool cmp(qry a, qry b){
    return a.r < b.r;
}

vector<qry> qq[1000], sp;

void MO(vector<qry> Q){
    if(Q.empty()) return;
    vector<int> inc(1, 0);
    vector<ll> pre(1, 0);
    ll r_ans = 0, rb = r - 1;
    for(qry q:Q){
        ll lb = q.l - 1, l_ans = 0, k;
        vector<int> finc(1, 0);
        while(rb < q.r){
            ++rb;
            int x = a[rb];
            if(x < inc.back()) r_ans += (inc.back() - x), x = inc.back();
            inc.pb(x);
            pre.pb(pre.back() + x);
        }
        while(lb < r - 1){
            ++lb;
            int x = a[lb];
            if(x < finc.back()) l_ans += (finc.back() - x), x = finc.back();
            finc.pb(x);
        }
        k = (lower_bound(inc.begin(), inc.end(), finc.back()) - inc.begin()) - 1;
        ans[q.t] = l_ans + r_ans + ((ll) finc.back() * k - pre[k]);
    }
}

void solve(){
    cin >> n >> m;
    int k = ceil(pow(n, 0.5));
    for(int i = 1; i <= n; ++i)
        cin >> a[i];
    for(int i = 1, l, r; i <= m; ++i){
        cin >> l >> r;
        qry Q(l, r, i);
        if(l / k != r / k) qq[l / k].pb(Q);
        else sp.pb(Q);
    }
    for(int i = 0; i <= n / k; ++i){
        sort(qq[i].begin(), qq[i].end(), cmp);
        r = (i + 1) * k;
        MO(qq[i]);
    }
    for(qry q:sp){
        vector<int> inc(1, 0);
        for(int i = q.l; i <= q.r; ++i){
            int x = a[i];
            if(inc.back() > x) ans[q.t] += (inc.back() - x), x = inc.back();
            inc.pb(x);
        }
    }
    for(int i = 1; i <= m; ++i) cout << ans[i] << '\n';
}

signed main(){
    starburst
    int t = 1; //cin >> t;
    while(t--) solve();
}
