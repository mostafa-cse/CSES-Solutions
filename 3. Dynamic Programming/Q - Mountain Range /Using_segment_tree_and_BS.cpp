#include <bits/stdc++.h>
using namespace std;
 
const int nmax = 2e5 + 5;
int vmax[nmax][20], n, acces_max[4 * nmax], l_max[nmax], putere[nmax];
pair<int, int> v[nmax];
 
void actualizare(int nod, int st, int dr, int a, int b, int val) {
    if (a <= st && dr <= b)
        acces_max[nod] = max(acces_max[nod], val);
    else if (!(dr < a || st > b)) {
        int mij = (st + dr) / 2;
        actualizare(2 * nod, st, mij, a, b, val);
        actualizare(2 * nod + 1, mij + 1, dr, a, b, val);
    }
}
 
int maxim(int nod, int st, int dr, int poz) {
    if (st == dr) return acces_max[nod];
    int mij = (st + dr) / 2;
    if (poz <= mij)
        return max(acces_max[nod], maxim(2 * nod, st, mij, poz));
    else
        return max(acces_max[nod], maxim(2 * nod + 1, mij + 1, dr, poz));
}
 
int query_max(int l, int r) {
    if (l > r) return 0;
    int len = r - l + 1;
    int k = putere[len];
    return max(vmax[l][k], vmax[r - (1 << k) + 1][k]);
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    cin >> n;
 
    // Precompute log base 2
    for (int i = 2; i <= n; i++)
        putere[i] = putere[i / 2] + 1;
 
    for (int i = 1; i <= n; i++) {
        cin >> v[i].first;
        v[i].second = i;
        vmax[i][0] = v[i].first;
    }
 
    // Build Sparse Table
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            vmax[i][j] = max(vmax[i][j - 1], vmax[i + (1 << (j - 1))][j - 1]);
        }
    }
 
    sort(v + 1, v + n + 1); // sort by value ascending
 
    for (int i = n; i >= 1; i--) {
        int pos = v[i].second;
        l_max[pos] = maxim(1, 1, n, pos) + 1;
 
        // Right binary search
        if (pos < n) {
            int lo = pos + 1, hi = n, best = pos;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                if (query_max(pos + 1, mid) < v[i].first) {
                    best = mid;
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
            if (best > pos)
                actualizare(1, 1, n, pos + 1, best, l_max[pos]);
        }
 
        // Left binary search
        if (pos > 1) {
            int lo = 1, hi = pos - 1, best = pos;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                if (query_max(mid, pos - 1) < v[i].first) {
                    best = mid;
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            }
            if (best < pos)
                actualizare(1, 1, n, best, pos - 1, l_max[pos]);
        }
    }
 
    // Final result
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, l_max[i]);
    cout << ans << '\n';
 
    return 0;
}