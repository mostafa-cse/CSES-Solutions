// https://cses.fi/problemset/hack/2081/entry/14782110/
#include <bits/stdc++.h>
#define int long long
using namespace std;
vector<int> tree[200005];
int n, k1, k2;
int answer;
int getSuffixValue(deque<int> &suffix, int index) {
    if (index < 0) {
        return suffix[0];
    }
    if (index >= suffix.size()) {
        return 0;
    }
    return suffix[index];
}
void mergeSuffixArrays(deque<int> &suffixA, deque<int> &suffixB) {
    if (suffixA.size() < suffixB.size()) {
        swap(suffixA, suffixB);
    }

    for (int i = 0; i < suffixB.size(); i++) {
        answer += 1LL * (getSuffixValue(suffixB, i) - getSuffixValue(suffixB, i + 1)) * (getSuffixValue(suffixA, k1 - i) - getSuffixValue(suffixA, k2 - i + 1));
    }

    for (int i = 0; i < suffixB.size(); i++) {
        suffixA[i] += suffixB[i];
    }
}
deque<int> calculateSuffix(int node, int parent) {
    deque<int> suffixParent{1};
    for (int child : tree[node]) {
        if (child != parent) {
            deque<int> suffixChild = calculateSuffix(child, node);
            suffixChild.push_front(suffixChild.front());
            mergeSuffixArrays(suffixParent, suffixChild);
        }
    }
    return suffixParent;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> k1 >> k2;

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    calculateSuffix(1, 0);
    cout << answer;
    return 0;
}
