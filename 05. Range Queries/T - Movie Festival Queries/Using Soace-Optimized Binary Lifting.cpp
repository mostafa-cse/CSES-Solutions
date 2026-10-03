#include <bits/stdc++.h>
using namespace std;

struct ParentJump {
    vector<int> parent;
    vector<int> depth;
    vector<int> jump;

    explicit ParentJump(int maxCoord = 0) {
        parent.assign(maxCoord + 1, 0);
        depth.assign(maxCoord + 1, 0);
        jump.assign(maxCoord + 1, 0);
    }

    inline void addNode(int i) {
        int p = parent[i];
        depth[i] = depth[p] + 1;

        if (depth[p] - depth[jump[p]] == depth[jump[p]] - depth[jump[jump[p]]]) {
            jump[i] = jump[jump[p]];
        } else {
            jump[i] = p;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<pair<int,int>> segments(n);
    int maxCoord = 0;
    for (int i = 0; i < n; ++i) {
        int a, b; cin >> a >> b;
        segments[i] = {a, b};
        maxCoord = max(maxCoord, max(a, b));
    }

    vector<pair<int,int>> queries(q);
    for (int i = 0; i < q; ++i) {
        int L, R; cin >> L >> R;
        queries[i] = {L, R};
        maxCoord = max(maxCoord, max(L, R));
    }

    ParentJump pj(maxCoord);

    for (auto [a, b] : segments) {
        if (b >= 0 && b <= maxCoord) {
            pj.parent[b] = max(pj.parent[b], max(0, a));
        }
    }

    for (int i = 1; i <= maxCoord; ++i) {
        pj.parent[i] = max(pj.parent[i], pj.parent[i - 1]);
        pj.parent[i] = min(pj.parent[i], i);
        pj.addNode(i);
    }

    for (auto [L, R] : queries) {
        L = max(L, 0);
        R = min(R, maxCoord);

        int startR = R;
        int stepsStart = pj.depth[startR];

        while (L < R) {
            if (pj.jump[R] >= L) {
                R = pj.jump[R];
            } else {
                R = pj.parent[R];
            }
        }

        int stepsEnd = pj.depth[R];
        int answer = stepsStart - stepsEnd - (L > R);
        cout << answer << '\n';
    }
    return 0;
}
