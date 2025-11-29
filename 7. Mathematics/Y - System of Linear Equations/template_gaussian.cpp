#include <bits/stdc++.h>
#define int long long
using namespace std;
const int Mod = 1e9 + 7;
struct Gaussian_Elimination{
    int m, n;
    vector<vector<int>> mat;
    Gaussian_Elimination(int n, int m, vector<vector<int>> matrix) : n(n), m(m), mat(matrix) {}
    int modexpo(int a, int p) {
        int res = 1;
        while (p) {
            if(p & 1) {
                res = (a * res) % Mod;
            }
            p >>= 1;
            a = (a * a) % Mod;
        }
        return res;
    }
    int inverse(int val) { return modexpo((val % Mod + Mod) % Mod, Mod - 2); }
    void multiply(int row, int x){
        x = (x % Mod + Mod) % Mod;
        for (int i = 0; i <= m; i++) {
            mat[row][i] = (mat[row][i] * x) % Mod;
        }
    }
    void subtract(int row1, int row2, int x) {
        x = (x % Mod + Mod) % Mod;
        for (int i = 0; i <= m; i++) {
            int sub = (mat[row1][i] * x) % Mod;
            mat[row2][i] = (mat[row2][i] - sub) % Mod;
            if (mat[row2][i] < 0) mat[row2][i] += Mod;
        }
    }
    vector<int> apply() {
        vector<int> chosen(n, -1);
        for (int i = 0; i < n; i++) {
            bool found = false;
            for (int j = 0; j < m; j++) {
                if (mat[i][j] % Mod) {
                    chosen[i] = j;
                    found = true;
                    multiply(i, inverse(mat[i][j]));
                    break;
                }
            }
            if (!found && (mat[i][m] % Mod)) {
                return {};
            }

            if (found) {
                for (int j = 0; j < n; j++) {
                    if (i == j || mat[j][chosen[i]] == 0) {
                        continue;
                    }
                    subtract(i, j, mat[j][chosen[i]]);
                }
            }
        }
        vector<int> ans;
        ans.reserve(m);
        for (int i = 0; i < m; i++) {
            bool found = false;
            for (int j = 0; j < n; j++) {
                if (chosen[j] == i) {
                    ans.push_back((mat[j][m] % Mod + Mod) % Mod);
                    found = true;
                    break;
                }
            }
            if (!found) {
                ans.push_back(0);
            }
        }
        return ans;
    }
};
signed main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> mat(n, vector<int>(m + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            cin >> mat[i][j];
            mat[i][j] %= Mod; if (mat[i][j] < 0) mat[i][j] += Mod;
        }
    }
    Gaussian_Elimination equation(n, m, mat);
    vector<int> ans = equation.apply();

    if (ans.empty()) {
        cout << -1;
    } else {
        for (int i : ans) {
            cout << i << " ";
        }
        cout << '\n';
    }
    return 0;
}
