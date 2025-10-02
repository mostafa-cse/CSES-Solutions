

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MAXN = 200005;

int n, m;
ll a[MAXN], ans[MAXN];

struct Query {
    int l, r, idx;
    Query(int l = 0, int r = 0, int idx = 0) : l(l), r(r), idx(idx) {}
};

// Compare queries by right endpoint
bool compareByRight(const Query& a, const Query& b) {
    return a.r < b.r;
}

vector<Query> blockQueries[1000], sameBlockQueries;
int blockRight = 0;

// Process queries that span multiple blocks
void processBlockQueries(const vector<Query>& queries) {
    if (queries.empty()) return;
    vector<int> increasing(1, 0);
    vector<ll> prefixSum(1, 0);
    ll rightAnswer = 0;
    int rightBound = blockRight - 1;
    for (const Query& q : queries) {
        int leftBound = q.l - 1;
        ll leftAnswer = 0;
        vector<int> leftIncreasing(1, 0);
        // Extend right pointer
        while (rightBound < q.r) {
            ++rightBound;
            int x = a[rightBound];
            if (x < increasing.back()) {
                rightAnswer += (increasing.back() - x);
                x = increasing.back();
            }
            increasing.push_back(x);
            prefixSum.push_back(prefixSum.back() + x);
        }
        // Extend left pointer
        while (leftBound < blockRight - 1) {
            ++leftBound;
            int x = a[leftBound];
            if (x < leftIncreasing.back()) {
                leftAnswer += (leftIncreasing.back() - x);
                x = leftIncreasing.back();
            }
            leftIncreasing.push_back(x);
        }
        int k = (lower_bound(increasing.begin(), increasing.end(), leftIncreasing.back()) - increasing.begin()) - 1;
        ans[q.idx] = leftAnswer + rightAnswer + (ll)leftIncreasing.back() * k - prefixSum[k];
    }
}

// Process queries that are fully within a single block
void processSameBlockQueries() {
    for (const Query& q : sameBlockQueries) {
        vector<int> increasing(1, 0);
        for (int i = q.l; i <= q.r; ++i) {
            int x = a[i];
            if (increasing.back() > x) {
                ans[q.idx] += (increasing.back() - x);
                x = increasing.back();
            }
            increasing.push_back(x);
        }
    }
}

void solve() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    int blockSize = ceil(sqrt(n));
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; ++i) {
        int l, r;
        cin >> l >> r;
        Query q(l, r, i);
        if (l / blockSize != r / blockSize) {
            blockQueries[l / blockSize].push_back(q);
        } else {
            sameBlockQueries.push_back(q);
        }
    }
    for (int i = 0; i <= n / blockSize; ++i) {
        sort(blockQueries[i].begin(), blockQueries[i].end(), compareByRight);
        blockRight = (i + 1) * blockSize;
        processBlockQueries(blockQueries[i]);
    }
    processSameBlockQueries();
    for (int i = 1; i <= m; ++i) {
        cout << ans[i] << '\n';
    }
}

int main() {
    solve();
    return 0;
}
