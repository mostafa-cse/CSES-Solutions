#include <bits/stdc++.h>
using namespace std;

// ================== Fast I/O ==================
static inline void fast_io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

// ================== Typedefs ==================
using ll = long long;
using ull = unsigned long long;
using ld = long double;

// ================== Constants ==================
constexpr ll MOD = 1'000'000'007LL; // change if needed
constexpr ll INFLL = (ll)4e18;
constexpr int INF = (int)1e9;

// ================== Utilities ==================
template<class T> inline bool chmin(T &a, const T &b){ if(b < a){ a = b; return true; } return false; }
template<class T> inline bool chmax(T &a, const T &b){ if(b > a){ a = b; return true; } return false; }

static inline ll mod_add(ll a, ll b, ll m = MOD){ a %= m; b %= m; a += b; if(a >= m) a -= m; return a; }
static inline ll mod_sub(ll a, ll b, ll m = MOD){ a %= m; b %= m; a -= b; if(a < 0) a += m; return a; }
static inline ll mod_mul(ll a, ll b, ll m = MOD){ return (ll)((__int128)a * b % m); }

static inline ll mod_pow(ll a, ll e, ll m = MOD){
    ll r = 1 % m; a %= m;
    while(e > 0){ if(e & 1) r = mod_mul(r, a, m); a = mod_mul(a, a, m); e >>= 1; }
    return r;
}

static inline ll mod_inv(ll a, ll m = MOD){
    // m must be prime, a and m coprime
    return mod_pow((a % m + m) % m, m - 2, m);
}

// Random (deterministic seed from steady_clock)
static uint64_t RNG_STATE = chrono::steady_clock::now().time_since_epoch().count();
static inline uint64_t rng64(){
    RNG_STATE ^= RNG_STATE << 7; RNG_STATE ^= RNG_STATE >> 9; return RNG_STATE;
}

// ================== Combinatorics (mod prime) ==================
struct Comb {
    int n;
    ll mod;
    vector<ll> fact, ifact;
    Comb(): n(0), mod(MOD) {}
    Comb(int N, ll M = MOD){ init(N, M); }
    void init(int N, ll M = MOD){
        n = N; mod = M; fact.assign(n+1, 1); ifact.assign(n+1, 1);
        for(int i = 1; i <= n; ++i) fact[i] = mod_mul(fact[i-1], i, mod);
        ifact[n] = mod_inv(fact[n], mod);
        for(int i = n; i > 0; --i) ifact[i-1] = mod_mul(ifact[i], i, mod);
    }
    ll nCr(int N, int R) const {
        if(R < 0 || R > N) return 0;
        return mod_mul(fact[N], mod_mul(ifact[R], ifact[N-R], mod), mod);
    }
    ll nPr(int N, int R) const {
        if(R < 0 || R > N) return 0;
        return mod_mul(fact[N], ifact[N-R], mod);
    }
};

// ================== Disjoint Set Union ==================
struct DSU {
    int n; vector<int> p, sz;
    DSU() : n(0) {}
    DSU(int N){ init(N); }
    void init(int N){ n = N; p.resize(n); iota(p.begin(), p.end(), 0); sz.assign(n, 1); }
    int find(int x){ return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int a, int b){ a = find(a); b = find(b); if(a == b) return false; if(sz[a] < sz[b]) swap(a, b); p[b] = a; sz[a] += sz[b]; return true; }
    int size(int x){ return sz[find(x)]; }
};

// ================== Sieve (primes up to N) ==================
vector<int> sieve(int N){
    vector<int> primes; vector<bool> is(N+1, true);
    if(N >= 0) is[0] = false; if(N >= 1) is[1] = false;
    for(int i = 2; i * 1LL * i <= N; ++i){ if(is[i]) for(long long j = 1LL*i*i; j <= N; j += i) is[(size_t)j] = false; }
    for(int i = 2; i <= N; ++i) if(is[i]) primes.push_back(i);
    return primes;
}

// ================== Grid Directions ==================
const int DX4[4] = {1, 0, -1, 0};
const int DY4[4] = {0, 1, 0, -1};
const int DX8[8] = {1,1,0,-1,-1,-1,0,1};
const int DY8[8] = {0,1,1,1,0,-1,-1,-1};

// ================== Debug Helper ==================
#ifdef LOCAL
    #define DEBUG_VAR(x) cerr << "[" #x ": " << (x) << "]\n"
#else
    #define DEBUG_VAR(x) ((void)0)
#endif

// ================== Problem Solver ==================
void solve(){
    // Implement your solution here.
    // Example: read n, array, print sum
    int n; if(!(cin >> n)) return; vector<ll> a(n); for(int i=0;i<n;++i) cin >> a[i];
    ll s = 0; for(ll x: a) s += x; cout << s << '\n';
}

int main(){
    fast_io();
    // If multiple test cases, uncomment:
    // int T; cin >> T; while(T--) solve();
    // For single test case:
    solve();
    return 0;
}

/*
Compilation (macOS):
  g++ -std=c++17 -O2 -pipe -Wall -Wextra -Wshadow -o main cp_template.cpp
Run:
  ./main < input.txt
*/
