#pragma once
#include <vector>
#include <functional>
#include <cmath>

// SparseTable for idempotent, associative operations (e.g., min, max, gcd).
// Default builds RMQ (Range Minimum Query) over a vector<int>.
// For other types/ops, provide T and a binary op with identity.

template <typename T>
struct SparseTable {
    int n;
    int K; // floor(log2(n))
    std::vector<int> lg; // precomputed logs
    std::vector<std::vector<T>> st; // st[k][i] -> op over range [i, i + 2^k - 1]
    std::function<T(const T&, const T&)> op;

    SparseTable() : n(0), K(0) {}

    SparseTable(const std::vector<T>& a,
                std::function<T(const T&, const T&)> op)
        : n((int)a.size()), op(std::move(op)) {
        build(a);
    }

    void build(const std::vector<T>& a) {
        n = (int)a.size();
        if (n == 0) { K = 0; lg.clear(); st.clear(); return; }
        K = 32 - __builtin_clz(n); // ceil(log2(n)) but we use up to floor
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; ++i) lg[i] = lg[i >> 1] + 1;

        st.assign(K, std::vector<T>(n));
        st[0] = a;
        for (int k = 1; k < K; ++k) {
            int len = 1 << k;
            int half = len >> 1;
            for (int i = 0; i + len - 1 < n; ++i) {
                st[k][i] = op(st[k - 1][i], st[k - 1][i + half]);
            }
        }
    }

    // Query over inclusive range [l, r]. Requires op to be idempotent (RMQ/Max/GCD).
    T query(int l, int r) const {
        if (l > r) std::swap(l, r);
        int len = r - l + 1;
        int k = lg[len];
        return op(st[k][l], st[k][r - (1 << k) + 1]);
    }
};

// Convenience alias for RMQ over int with std::min
struct RMQInt {
    SparseTable<int> st;
    RMQInt() {}
    explicit RMQInt(const std::vector<int>& a)
        : st(a, [](const int& x, const int& y) { return std::min(x, y); }) {}
    void build(const std::vector<int>& a) {
        st = SparseTable<int>(a, [](const int& x, const int& y) { return std::min(x, y); });
    }
    int query(int l, int r) const { return st.query(l, r); }
};

/*
Usage:

#include "SparseTable.hpp"

int main() {
    std::vector<int> a = {5, 2, 6, 3, 1, 7};
    RMQInt rmq(a);
    // min on [1,4] -> 1
    int ans = rmq.query(1, 4);
}

// For custom type/op:
// SparseTable<long long> st_ll(arr, [](auto &x, auto &y){ return std::min(x, y); });
*/
