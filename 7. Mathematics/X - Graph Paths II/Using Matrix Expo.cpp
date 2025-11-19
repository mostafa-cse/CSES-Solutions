#include <bits/stdc++.h>
#define int long long
using namespace std;

const int INF = (1LL << 60);

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
        return Matrix(values);
    }

    Matrix operator*(const Matrix& other) const {
        assert(n_cols == other.n_rows);
        int n = n_rows, m = other.n_cols, K = n_cols;
        vector<vector<int>> result(n, vector<int>(m, INF));
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < K; k++) {
                if (mat[i][k] == INF) continue;
                for (int j = 0; j < m; j++) {
                    if (other.mat[k][j] == INF) continue;
                    result[i][j] = min(result[i][j], mat[i][k] + other.mat[k][j]);
                }
            }
        }
        return Matrix(result);
    }
};
Matrix pw(Matrix a, int p) {
    Matrix result = Matrix::identity_matrix(a.n_rows);
    while (p > 0) {
        if (p & 1)
            result = result * a;
        a = a * a;
        p >>= 1;
    }
    return result;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    if (!(cin >> n >> m >> k)) return 0;

    vector<vector<int>> mat(n, vector<int>(n, INF));

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        mat[u][v] = min(mat[u][v], w);
    }

    Matrix adj(mat);
    Matrix res = pw(adj, k);

    int ans = res.mat[0][n - 1];

    if (ans >= INF)
        cout << -1 << endl;
    else
        cout << ans << endl;
    return 0;
}
