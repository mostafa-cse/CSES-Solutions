#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MOD = 1e9 + 7;
const long long MOD2 = static_cast<long long>(MOD) * MOD;
struct Matrix {
    vector<vector<int>> mat;
    int n_rows, n_cols;

    Matrix() {}

    Matrix(vector<vector<int>> values)
        : mat(values), n_rows(values.size()), n_cols(values[0].size()) {}

    static Matrix identity_matrix(int n) {
        vector<vector<int>> values(n, vector<int>(n, 1e9));
        for (int i = 0; i < n; i++)
            values[i][i] = 0;
        return values;
    }

    Matrix operator*(const Matrix& other) const {
        int n = n_rows, m = other.n_cols;
        vector<vector<int>> result(n_rows, vector<int>(n_cols, 0));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                long long tmp = 1e9;
                for (int k = 0; k < n_cols; k++) {
                    tmp = min(mat[i][k] + other.mat[k][j], tmp);
                }
                result[i][j] = tmp;
            }

        return move(Matrix(move(result)));
    }
};
Matrix pw(Matrix a, int p) {
    Matrix result = Matrix::identity_matrix(a.n_cols);
    while (p > 0) {
        if (p & 1)
            result = a * result;
        a = a * a;
        p >>= 1;
    }
    return result;
}

signed main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> mat(n + 1, vector<int>(n + 1, 1e9));
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        mat[u - 1][v - 1] = min(mat[u - 1][v - 1], w);
    }

    Matrix res(mat);
    res = pw(mat, k);

    int ans = res.mat[0][n - 1];
    if (ans == 1e18)
        ans = -1;
    cout << ans % MOD << endl;
    return 0;
}
