#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MOD = 1e9 + 7;
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
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
                    tmp %= MOD;
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

    vector<vector<int>> f = {
                                {1, 1, 1, 1, 1, 1}, // a+b+c+d+e+f a b c d e
                                {1, 0, 0, 0, 0, 0}, //       a     0 0 0 0 0
                                {0, 1, 0, 0, 0, 0}, //       0     b 0 0 0 0
                                {0, 0, 1, 0, 0, 0}, //       0     0 c 0 0 0
                                {0, 0, 0, 1, 0, 0}, //       0     0 0 d 0 0
                                {0, 0, 0, 0, 1, 0} //        0     0 0 0 e 0
                            };
    Matrix res(f);
    res = pw(res, n);
    cout << res.mat[0][0] << endl;
    return 0;
}


