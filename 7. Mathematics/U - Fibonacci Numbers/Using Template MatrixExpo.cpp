#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MOD = 1e9 + 7;
const long long MOD2 = static_cast<long long>(MOD) * MOD;
struct Matrix {
    vector<vector<int>> mat;
    int n_rows, n_cols;

    Matrix(int nRow, int mCol) : n_rows(nRow), n_cols(mCol), mat(nRow, vector<int>(mCol, 0)) {}
    Matrix(vector<vector<int>> values) : mat(values), n_rows(values.size()), n_cols(values[0].size()) {}

    static Matrix identity_matrix(int n) {
        vector<vector<int>> values(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++)
            values[i][i] = 1;
        return values;
    }

    Matrix operator*(const Matrix& other) const {
        int n = n_rows, m = other.n_cols;
        vector<vector<int>> result(n_rows, vector<int>(n_cols, 0));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                long long tmp = 0;
                for (int k = 0; k < n_cols; k++) {
                    tmp += mat[i][k] * 1ll * other.mat[k][j];
                    while (tmp >= MOD2)
                        tmp -= MOD2;
                }
                result[i][j] = tmp % MOD;
            }
        return move(Matrix(move(result)));
    }

    inline bool is_square() const { return n_rows == n_cols; }
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
    int n;
    cin >> n;

    if (n <= 1) {
        return cout << n << endl, 0;
    }
    Matrix fibo(2, 2);
    fibo.mat[0][0] = fibo.mat[0][1] = fibo.mat[1][0] = 1;
    Matrix ans = pw(fibo, n - 1);
    cout << ans.mat[0][0];
    return 0;
}
