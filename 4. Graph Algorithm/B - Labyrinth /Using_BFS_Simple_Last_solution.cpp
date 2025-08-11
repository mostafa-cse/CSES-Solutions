#include<bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);  cout.tie(0);
    int n, m;
    cin >> n >> m;

    vector<vector<char>> g(n + 1, vector<char>(m + 1));
    pair<int, int> start = {-1, -1}, end = {0, 0};
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> g[i][j];
            if (g[i][j] == 'A') {
                start.first = i;
                start.second = j;
            } else if (g[i][j] == 'B') {
                end.first = i;
                end.second = j;
            }
        }
    }
    map<pair<int, int>, char> dir_ch;
    dir_ch[{1, 0}] = 'D', dir_ch[{-1, 0}] = 'U';
    dir_ch[{0, 1}] = 'R', dir_ch[{0, -1}] = 'L';

    if (start.first == -1) {
        cout << "NO" << endl;
    } else {
        vector<vector<char>> par(n + 1, vector<char>(m + 1, 'O'));
        vector<vector<int>> vis(n + 1, vector<int>(m + 1, 0));
        queue<pair<int, int>> q;

        q.push({start});
        par[start.first][start.second] = {'P'};
        vis[start.first][start.second] = 1;
        while (!q.empty()) {
            const auto [i, j] = q.front();
            q.pop();


            for (int d = 0; d < 4; d++) {
                int ni = i + dx[d];
                int nj = j + dy[d];
                if (ni > 0 and nj > 0 and  ni <= n and nj <= m and vis[ni][nj] == 0 and g[ni][nj] != '#') {
                    par[ni][nj] = dir_ch[{dx[d], dy[d]}];
                    vis[ni][nj] = 1;
                    q.push({ni, nj});
                }
            }
        }

        /*
            Direction Map : 
            dir_ch[{1, 0}] = 'D', dir_ch[{-1, 0}] = 'U';
            dir_ch[{0, 1}] = 'R', dir_ch[{0, -1}] = 'L';
        */
        if (vis[end.first][end.second] == 1) {
            int i = end.first;
            int j = end.second;
            string str = "";
            while (par[i][j] != 'P') {
                str += par[i][j];
                int ni, nj;
                if (par[i][j] == 'D') {
                    ni = i - 1;
                    nj = j - 0;
                } else if (par[i][j] == 'R') {
                    ni = i - 0;
                    nj = j - 1;
                } else if (par[i][j] == 'L') {
                    ni = i;
                    nj = j + 1;
                } else if (par[i][j] == 'U') {
                    ni = i + 1;
                    nj = j;
                } else {
                    assert(false);
                }
                i = ni;
                j = nj;
            }
            cout << "YES" << endl;
            cout << str.size() << endl;
            for (int i = str.size() - 1; i >= 0; i--) {
                cout << str[i];
            }
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
