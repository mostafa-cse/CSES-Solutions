#include <bits/stdc++.h>
using namespace std;

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};
int p[48];
bool vis[9][9];
string path;
int getIdx(char c) {
    if (c == 'U') {
        return 0;
    } else if (c == 'R') {
        return 1;
    } else if (c == 'D') {
        return 2;
    }
    return 3;
}
int tryPath(int idx, int r, int c) {
    if ((vis[r][c - 1] && vis[r][c + 1]) && (!vis[r - 1][c] && !vis[r + 1][c])) {
        return 0;
    }
    if ((vis[r - 1][c] && vis[r + 1][c]) && (!vis[r][c - 1] && !vis[r][c + 1])) {
        return 0;
    }

    if (r == 7 && c == 1) {
        return (idx == 48);
    }

    if (idx == 48) return 0;

    int ret = 0;
    vis[r][c] = true;
    if (path[idx] != '?') {
        int nxtR = r + dr[getIdx(path[idx])];
        int nxtC = c + dc[getIdx(path[idx])];
        if (!vis[nxtR][nxtC]) ret += tryPath(idx + 1, nxtR, nxtC);
    } else {
        for (int i = 0; i < 4; i++) {
            int nxtR = r + dr[i];
            int nxtC = c + dc[i];
            if (vis[nxtR][nxtC]) continue;
            ret += tryPath(idx + 1, nxtR, nxtC);
        }
    }
    vis[r][c] = false;
    return ret;
}

int main() {
    cin >> path;
    for (int i = 0; i < 9; i++) {
        vis[0][i] = vis[8][i] = true;
        vis[i][0] = vis[i][8] = true;
    }
    int ans = tryPath(0, 1, 1);
    cout << ans << endl;
    return 0;
}
