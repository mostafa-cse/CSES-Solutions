// Gemini
#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 105;
int n; // Global N to access in Matrix struct

// Matrix Structure
struct Matrix {
    long long mat[MAXN][MAXN];

    Matrix() {
        for (int i = 0; i < MAXN; i++)
            for (int j = 0; j < MAXN; j++)
                mat[i][j] = 0;
    }

    // Function to create an Identity Matrix
    static Matrix identity(int size) {
        Matrix res;
        for(int i=0; i<size; i++) res.mat[i][i] = 1;
        return res;
    }
};

// Multiply two matrices: A * B
Matrix multiply(const Matrix& A, const Matrix& B) {
    Matrix C;
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            if (A.mat[i][k] == 0) continue; // Optimization
            for (int j = 0; j < n; j++) {
                C.mat[i][j] = (C.mat[i][j] + A.mat[i][k] * B.mat[k][j]) % MOD;
            }
        }
    }
    return C;
}

// Add two matrices: A + B
Matrix add(const Matrix& A, const Matrix& B) {
    Matrix C;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C.mat[i][j] = (A.mat[i][j] + B.mat[i][j]) % MOD;
        }
    }
    return C;
}

// Recursive function to return pair { A^k, Sum(A^1...A^k) }
// Returns: pair<Power Matrix, Sum Matrix>
pair<Matrix, Matrix> calc_geo_sum(Matrix A, int k) {
    // Base case: k=1 -> Power is A, Sum is A
    if (k == 1) {
        return {A, A};
    }

    if (k % 2 == 1) {
        // If k is odd: S(k) = S(k-1) + A^k
        pair<Matrix, Matrix> prev = calc_geo_sum(A, k - 1);
        Matrix prevPower = prev.first; // A^(k-1)
        Matrix prevSum = prev.second;  // Sum(k-1)

        // Calculate A^k = A^(k-1) * A
        Matrix currPower = multiply(prevPower, A);

        // Calculate Sum(k) = Sum(k-1) + A^k
        Matrix currSum = add(prevSum, currPower);

        return {currPower, currSum};
    } else {
        // If k is even (k = 2x): S(2x) = S(x) * (I + A^x)
        // Also need A^2x = A^x * A^x
        pair<Matrix, Matrix> half = calc_geo_sum(A, k / 2);
        Matrix halfPower = half.first; // A^x
        Matrix halfSum = half.second;  // S(x)

        // Total Power A^k = A^x * A^x
        Matrix totalPower = multiply(halfPower, halfPower);

        // Total Sum S(k) = S(x) + S(x) * A^x
        Matrix secondPart = multiply(halfSum, halfPower);
        Matrix totalSum = add(halfSum, secondPart);

        return {totalPower, totalSum};
    }
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int m, k;
    if (cin >> n >> m >> k) {
        Matrix adj;
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            // Convert 1-based index to 0-based
            adj.mat[u - 1][v - 1]++;
        }

        // Calculate sum of powers from A^1 to A^k
        pair<Matrix, Matrix> result = calc_geo_sum(adj, k);

        // result.second is the Sum Matrix
        // We want paths from node 1 (index 0) to node n (index n-1)
        cout << result.second.mat[0][n - 1] << endl;
    }
    return 0;
}
// ChatGpt
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;

struct Matrix {
    int n;
    vector<vector<long long>> a;

    Matrix(int n, bool ident=false) : n(n), a(n, vector<long long>(n, 0)) {
        if (ident) for (int i = 0; i < n; ++i) a[i][i] = 1;
    }

    Matrix operator*(const Matrix &o) const {
        Matrix r(n);
        for (int i = 0; i < n; ++i) {
            for (int p = 0; p < n; ++p) {              // renamed k -> p
                if (a[i][p] == 0) continue;
                long long v = a[i][p];
                for (int j = 0; j < n; ++j) {
                    r.a[i][j] = (r.a[i][j] + v * o.a[p][j]) % MOD;
                }
            }
        }
        return r;
    }
};

Matrix power(Matrix base, long long exp) {
    Matrix result(base.n, true);
    while (exp > 0) {
        if (exp & 1) result = result * base;
        base = base * base;
        exp >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m, k;
    if (!(cin >> n >> m >> k)) return 0;

    Matrix A((int)n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        A.a[a-1][b-1] = (A.a[a-1][b-1] + 1) % MOD;
    }

    int N = 2 * (int)n;
    Matrix M(N);

    // Top-left block = A
    for (int i = 0; i < (int)n; ++i)
        for (int j = 0; j < (int)n; ++j)
            M.a[i][j] = A.a[i][j];

    // Top-right block = I
    for (int i = 0; i < (int)n; ++i)
        M.a[i][i + (int)n] = 1;

    // Bottom-right block = I
    for (int i = 0; i < (int)n; ++i)
        M.a[i + (int)n][i + (int)n] = 1;

    Matrix Mk = power(M, k);

    // S0 = sum_{i=0..k-1} A^i  (top-right block)
    Matrix S0((int)n);
    for (int i = 0; i < (int)n; ++i)
        for (int j = 0; j < (int)n; ++j)
            S0.a[i][j] = Mk.a[i][j + (int)n];

    // S = A * S0 = A + A^2 + ... + A^k
    Matrix S = A * S0;

    long long ans = S.a[0][(int)n - 1];
    // include 0-length path if start == end (node 1 == node n)
    if (n == 1) ans = (ans + 1) % MOD;

    cout << ans << "\n";
    return 0;
}

