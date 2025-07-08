
using namespace std;
#define MAXN 3010
char s[MAXN][MAXN];
int a[MAXN][MAXN], n;
int ans[MAXN * 2], vis[MAXN][MAXN];
struct node
{
    int x, y;
};
queue<node> q, q2;
void bfs()
{
    vector<vector<bool>> vis2(MAXN, vector<bool>(MAXN, false));
    vector<pair<int, int>> curr, next;
    curr.emplace_back(1, 1);
    string res;
    res += s[1][1];
    vis2[1][1] = true;
    for (int step = 1; step < 2 * n - 1; ++step) {
        char mn = 'Z' + 1;
        next.clear();
        for (auto [x, y] : curr) {
            if (x + 1 <= n) mn = min(mn, s[x + 1][y]);
            if (y + 1 <= n) mn = min(mn, s[x][y + 1]);
        }
        for (auto [x, y] : curr) {
            if (x + 1 <= n && s[x + 1][y] == mn && !vis2[x + 1][y]) {
                next.emplace_back(x + 1, y);
                vis2[x + 1][y] = true;
            }
            if (y + 1 <= n && s[x][y + 1] == mn && !vis2[x][y + 1]) {
                next.emplace_back(x, y + 1);
                vis2[x][y + 1] = true;
            }
        }
        res += mn;
        curr.swap(next);
    }
    cout << res << '\n';
}
int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            char c;
            cin >> c;
            a[i][j] = c - 'A';
            s[i][j] = c;
        }
    bfs();
    return 0;
}
