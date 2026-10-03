#include <bits/stdc++.h>
using namespace std;

vector<int> manacher(const string& s) {
    string t = "^";
    for (char c : s) {
        t += "#";
        t += c;
    }
    t += "#$";

    int n = t.size();
    vector<int> p(n, 0);
    int l = 0, r = 0;
    for (int i = 1; i < n - 1; i++) {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while (t[i - p[i]] == t[i + p[i]]) {
            p[i]++;
        }
        if (i + p[i] > r) {
            l = i - p[i];
            r = i + p[i];
        }
    }
    return p;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    vector<int> radii = manacher(s);
    int m = radii.size();

    vector<vector<int>> expire(m);
    for (int c = 1; c < m - 1; c++) {
        int end_idx = c + radii[c] - 1;
        expire[end_idx].push_back(c);
    }

    set<int> active_centers;
    for (int end_points = 1; end_points < m - 1; end_points++) {
        active_centers.insert(end_points);
        for (int c : expire[end_points - 1]) {
            active_centers.erase(c);
        }
        if (end_points % 2 == 0) {
            int left_most_center = *active_centers.begin();
            cout << (end_points - left_most_center + 1) << " ";
        }
    }
    return 0;
}
