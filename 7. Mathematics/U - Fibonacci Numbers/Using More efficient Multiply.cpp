#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MOD = 1e9 + 7;
struct Matrix {
    vector<vector<int>> mat;
    int n_rows, n_cols;
    Matrix() {}
    Matrix(vector<vector<int>> values)
        : mat(values), n_rows(values.size()), n_cols(values[0].size()) {}

    static Matrix identity_matrix(int n) {
        vector<vector<int>> values(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++)
            values[i][i] = 1;
        return Matrix(values);
    }
    Matrix operator*(const Matrix& other) const {
        vector<vector<int>> result(2, vector<int>(2, 0));
        result[0][0] = ((mat[0][0] * other.mat[0][0]) % MOD + (mat[0][1] * other.mat[1][0]) % MOD) % MOD;
        result[0][1] = ((mat[0][0] * other.mat[0][1]) % MOD + (mat[0][1] * other.mat[1][1]) % MOD) % MOD;
        result[1][1] = ((mat[1][0] * other.mat[0][1]) % MOD + (mat[1][1] * other.mat[1][1]) % MOD) % MOD;
        result[1][0] = ((mat[1][0] * other.mat[0][0]) % MOD + (mat[1][1] * other.mat[1][0]) % MOD) % MOD;
        return Matrix(result);
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
    int n;
    cin >> n;

    if (n <= 1) {
        return cout << n << endl, 0;
    }

    vector<vector<int>> f = {{1, 1}, {1, 0}};
    Matrix fibo(f);

    Matrix ans = pw(fibo, n - 1);
    cout << ans.mat[0][0] << '\n';
    return 0;
}
