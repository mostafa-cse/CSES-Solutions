#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;

    vector<string> g(n);
    int start_x = -1, start_y = -1, end_x = -1, end_y = -1;
    
    for (int i = 0; i < n; i++) {
        cin >> g[i];
        for (int j = 0; j < m; j++) {
            if (g[i][j] == 'A') {
                start_x = i, start_y = j;
            } else if (g[i][j] == 'B') {
                end_x = i, end_y = j;
            }
        }
    }
    
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<vector<pair<int, int>>> parent(n, vector<pair<int, int>>(m, {-1, -1}));
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    string dir_chars = "UDLR";
    
    queue<pair<int, int>> q;
    q.push({start_x, start_y});
    visited[start_x][start_y] = true;
    
    bool found = false;
    while (!q.empty() && !found) {
        auto [x, y] = q.front();
        q.pop();
        
        if (x == end_x && y == end_y) {
            found = true;
            break;
        }
        
        for (int d = 0; d < 4; d++) {
            int nx = x + directions[d].first;
            int ny = y + directions[d].second;
            
            if (nx >= 0 && ny >= 0 && nx < n && ny < m && 
                g[nx][ny] != '#' && !visited[nx][ny]) {
                visited[nx][ny] = true;
                parent[nx][ny] = {x, y};
                q.push({nx, ny});
            }
        }
    }
    
    if (!found) {
        cout << "NO\n";
        return 0;
    }
    
    cout << "YES\n";
    
    string path = "";
    int curr_x = end_x, curr_y = end_y;
    
    while (parent[curr_x][curr_y].first != -1) {
        int prev_x = parent[curr_x][curr_y].first;
        int prev_y = parent[curr_x][curr_y].second;
        
        for (int d = 0; d < 4; d++) {
            if (prev_x + directions[d].first == curr_x && 
                prev_y + directions[d].second == curr_y) {
                path += dir_chars[d];
                break;
            }
        }
        
        curr_x = prev_x;
        curr_y = prev_y;
    }
    
    reverse(path.begin(), path.end());
    cout << path.length() << "\n";
    cout << path << "\n";
    
    return 0;
}
