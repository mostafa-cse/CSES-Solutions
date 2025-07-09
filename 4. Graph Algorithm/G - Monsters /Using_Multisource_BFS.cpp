#include <bits/stdc++.h>
using namespace std;
map<char, pair<int, int>> dir = {
    {'U', {1, 0}}, {'L', {0, 1}}, {'D', {-1, 0}}, {'R', {0, -1}}};
int main() {
    int a, b, x, y;
    cin >> a >> b;
    vector<string> Map(a);
    queue<pair<int, int>> q;
    for (int i = 0; i < a; i++) {
        cin >> Map[i];
        for (int j = 0; j < b; j++)
            if (Map[i][j] == 'M')
                q.emplace(i, j);
            else if (Map[i][j] == 'A')
                x = i, y = j;
    }
    q.emplace(x, y);
    while (q.size()) {
        x = q.front().first, y = q.front().second;
        q.pop();
        if ((!x || x == a - 1 || !y || y == b - 1) && Map[x][y] != 'M') {
            string ans = "";
            while (Map[x][y] != 'A') {
                char c = Map[x][y];
                ans += c;
                x += dir[c].first;
                y += dir[c].second;
            }
            cout << "YES" << endl;
            cout << ans.size() << endl;
            cout << string(ans.rbegin(), ans.rend());
            return 0;
        }
        for (auto& [d, val] : dir) {
            int xx = x - val.first, yy = y - val.second;
            if (xx < 0 || xx >= a || yy < 0 || yy >= b || Map[xx][yy] != '.') {
                continue;
            }
            Map[xx][yy] = Map[x][y] != 'M' ? d : Map[x][y];
            q.emplace(xx, yy);
        }
    }
    cout << "NO";
    return 0;
}