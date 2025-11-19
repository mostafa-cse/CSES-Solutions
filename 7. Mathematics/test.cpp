#include <bits/stdc++.h>
#define int long long
using namespace std;
const int INF = 2e18;
struct Matrix {
    vector<vector<int>> mat;
    int n_rows, n_cols;

    Matrix() {}

    Matrix(vector<vector<int>> values)
        : mat(values), n_rows(values.size()), n_cols(values[0].size()) {}

    static Matrix identity_matrix(int n) {
        vector<vector<int>> values(n, vector<int>(n, INF));
        for (int i = 0; i < n; i++)
            values[i][i] = 0;
        return values;
    }

    Matrix operator*(const Matrix& other) const {
        int n = n_rows, m = other.n_cols;
        vector<vector<int>> result(n_rows, vector<int>(n_cols, INF));
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n_cols; k++) {
                if (mat[i][k] == INF) continue;

                for (int j = 0; j < m; j++) {
                    if (other.mat[k][j] == INF) continue;
                    result[i][j] = min(result[i][j], mat[i][k] + other.mat[k][j]);
                }
            }
        }
        return move(Matrix(move(result)));
    }

    inline bool is_square() const { return n_rows == n_cols; }
};
Matrix pw(Matrix a, int p) {
    Matrix result = Matrix::identity_matrix(a.n_cols);
    while (p > 0) {
        if (p & 1)
            result = result * a;
        a = a * a;
        p >>= 1;
    }
    return result;
}
signed main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> adj(n, vector<int>(n, INF));
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u -= 1, v -= 1;
        adj[u][v] = min(adj[u][v], w);
    }

    Matrix mat(adj);

    Matrix res = pw(mat, k);

    int ans = res.mat[0][n - 1];
    if (ans >= 1e18) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
    return 0;
}
