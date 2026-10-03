#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

// Maximum number of nodes in the tree
const int MAX_NODES = 200001;

// Adjacency list to represent the tree
std::vector<int> tree[MAX_NODES];

/**
 * @brief Computes the maximum matching in the subtree rooted at currentNode.
 *
 * @param currentNode The node currently being processed.
 * @param parentNode The parent of the current node (to avoid revisiting).
 * @return std::array<int, 2>
 *         - result[0]: Maximum matching size if currentNode is NOT matched.
 *         - result[1]: Maximum matching size if currentNode IS matched (as an endpoint).
 */
std::array<int, 2> computeMaximumMatching(int currentNode, int parentNode) {
    // Initialize DP values for the current node
    int unmatchedMaxMatching = 0; // Maximum matching size if currentNode is NOT matched
    int matchedMaxMatching = 0;   // Maximum matching size if currentNode IS matched

    for (int childNode : tree[currentNode]) {
        if (childNode == parentNode) continue; // Avoid revisiting the parent

        // Recursively compute DP values for the child
        std::array<int, 2> childMatching = computeMaximumMatching(childNode, currentNode);
        int childUnmatched = childMatching[0]; // Child's maximum matching if NOT matched
        int childMatched = childMatching[1];   // Child's maximum matching if matched

        // If currentNode is matched, consider matching it with this child
        matchedMaxMatching = std::max({
            unmatchedMaxMatching + childUnmatched + 1, // Match currentNode with childNode
            matchedMaxMatching + childMatched,         // Propagate previous matchings
            matchedMaxMatching + childUnmatched
        });

        // If currentNode is not matched, take the best from the child
        unmatchedMaxMatching += std::max(childUnmatched, childMatched);
    }

    return {unmatchedMaxMatching, matchedMaxMatching};
}

int main() {
    int numberOfNodes;
    std::cin >> numberOfNodes;

    // Read the edges and build the tree
    for (int i = 0; i < numberOfNodes - 1; ++i) {
        int nodeA, nodeB;
        std::cin >> nodeA >> nodeB;
        tree[nodeA].push_back(nodeB);
        tree[nodeB].push_back(nodeA);
    }

    // Start DFS from the root node (assumed to be 1)
    std::array<int, 2> result = computeMaximumMatching(1, 1);

    // Output the maximum matching size for the whole tree
    std::cout << std::max(result[0], result[1]) << std::endl;

    return 0;
}
