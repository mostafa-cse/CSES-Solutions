// more functionility version : https://cses.fi/problemset/hack/2081/entry/14785972/
#include <bits/stdc++.h>
#define int long long
using namespace std;
struct FrequencyBIT {
    int size = 0;
    vector<int> bit;

    void reset(int newSize) {
        size = max(0ll, newSize);
        bit.assign(size + 1, 0);
    }

    void add(int index, int delta) {
        for (int i = index; i <= size; i += i & -i)
            bit[i] += delta;
    }

    int prefixSum(int index) const {
        if (index < 1) return 0;
        int sum = 0;
        for (int i = min(index, size); i > 0; i -= i & -i)
            sum += bit[i];
        return sum;
    }

    int rangeSum(int leftIndex, int rightIndex) const {
        if (size == 0 || rightIndex < leftIndex) {
            return 0;
        }
        leftIndex = max(leftIndex, 1ll);
        rightIndex = min(rightIndex, size);
        if (leftIndex > rightIndex) {
            return 0;
        }
        return prefixSum(rightIndex) - prefixSum(leftIndex - 1);
    }
};

int n;
int minDistanceRequired, maxDistanceAllowed;
vector<vector<int>> adjacency;
vector<int> subtreeSize;
vector<char> isRemoved;
int totalPairs = 0;

int computeSubtreeSize(int node, int parent) {
    subtreeSize[node] = 1;
    for (int neighbor : adjacency[node]) {
        if (neighbor == parent || isRemoved[neighbor]) continue;
        subtreeSize[node] += computeSubtreeSize(neighbor, node);
    }
    return subtreeSize[node];
}

int findCentroid(int node, int parent, int componentSize) {
    for (int neighbor : adjacency[node]) {
        if (neighbor != parent && !isRemoved[neighbor] && subtreeSize[neighbor] > componentSize / 2) {
            return findCentroid(neighbor, node, componentSize);
        }
    }
    return node;
}


void gatherDepths(int startNode, int parent, int currentDepth, vector<int>& depths) {
    if (currentDepth > maxDistanceAllowed) return;
    depths.push_back(currentDepth);
    for (int neighbor : adjacency[startNode]) {
        if (neighbor == parent || isRemoved[neighbor]) continue;
        gatherDepths(neighbor, startNode, currentDepth + 1, depths);
    }
}

void countPairsThroughCentroid(int centroid) {
    vector<vector<int>> childDepths;
    int maxDepthSeen = 0;

    for (int neighbor : adjacency[centroid]) {
        if (isRemoved[neighbor]) continue;
        vector<int> depths;
        gatherDepths(neighbor, centroid, 1, depths);
        if (!depths.empty()) {
            maxDepthSeen = max(maxDepthSeen, *max_element(depths.begin(), depths.end()));
            childDepths.push_back(move(depths));
        }
    }

    FrequencyBIT bit;
    bit.reset(min(maxDistanceAllowed, maxDepthSeen) + 1);

    bit.add(1, 1);

    int currAns = 0;
    for (const auto& depths : childDepths) {
        for (int d : depths) {
            if (d > maxDistanceAllowed) continue;
            int leftIndex = minDistanceRequired - d + 1;
            int rightIndex = maxDistanceAllowed - d + 1;
            currAns += bit.rangeSum(leftIndex, rightIndex);
        }
        for (int d : depths) {
            int idx = d + 1;
            if (1 <= idx && idx <= bit.size) bit.add(idx, 1);
        }
    }
    totalPairs += currAns;
}

void decompose(int entryNode) {
    int componentSize = computeSubtreeSize(entryNode, -1);
    int centroid = findCentroid(entryNode, -1, componentSize);

    countPairsThroughCentroid(centroid);

    isRemoved[centroid] = true;
    for (int neighbor : adjacency[centroid]) {
        if (!isRemoved[neighbor]) decompose(neighbor);
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> minDistanceRequired >> maxDistanceAllowed;

    adjacency.assign(n, {});
    for (int i = 0; i < n - 1; ++i) {
        int a, b; cin >> a >> b;
        --a; --b;
        adjacency[a].push_back(b);
        adjacency[b].push_back(a);
    }

    subtreeSize.assign(n, 0);
    isRemoved.assign(n, false);

    decompose(0);
    cout << totalPairs << '\n';
    return 0;
}
