#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int N = 200001;
int adj[N][200];  // Simple adjacency list: adj[node][i] = neighbor
int adj_count[N]; // Number of neighbors for each node
bool used[N];     // Track if a node is already matched
int matching_count = 0;

void dfs(int node, int parent) {
    // Process all children first (post-order traversal)
    for (int i = 0; i < adj_count[node]; i++) {
        int child = adj[node][i];
        if (child == parent) continue;
        dfs(child, node);
    }

    // Try to match this node with its parent
    // Only if both are not already used in some matching
    if (parent != -1 && !used[node] && !used[parent]) {
        used[node] = true;
        used[parent] = true;
        matching_count++;
    }
}

int main(void) {
    int n;
    if (scanf("%d", &n) == EOF) return EXIT_FAILURE;

    // Initialize adjacency list
    for (int i = 0; i <= n; i++) {
        adj_count[i] = 0;
    }

    // Read edges and build adjacency list
    for (int i = 1; i < n; ++i) {
        int a, b;
        if (scanf("%d%d", &a, &b) == EOF) return EXIT_FAILURE;

        // Add edge a -> b
        adj[a][adj_count[a]] = b;
        adj_count[a]++;

        // Add edge b -> a
        adj[b][adj_count[b]] = a;
        adj_count[b]++;
    }

    dfs(1, 0);
    printf("%d\n", matching_count);
    return EXIT_SUCCESS;
}
