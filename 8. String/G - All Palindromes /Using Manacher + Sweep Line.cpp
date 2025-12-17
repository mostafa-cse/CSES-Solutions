#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
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

    // 1. Get Palindrome Radii
    vector<int> radii = manacher(s);
    dout(radii);
    int m = radii.size();

    // 2. Schedule Expiration Events
    // A center 'c' with radius 'r' covers the range [c - r + 1, c + r - 1] in t.
    // It stops being valid after index (c + r - 1).
    vector<vector<int>> expire(m);
    for (int c = 1; c < m - 1; c++) {
        int end_idx = c + radii[c] - 1;
        // end_idx is guaranteed to be < m because sentinels ^ and $ always break the palindrome match
        expire[end_idx].push_back(c);
    }

    // 3. Sweep-Line
    // Maintain 'active_centers' that extend at least to the current index.
    // The longest palindrome suffix ending at 'i' corresponds to the active center 'c'
    // that is furthest to the left (smallest index).
    set<int> active_centers;

    // Transformed String Structure: ^ # c1 # c2 # c3 # $
    // Indices:                      0 1 2  3 4  5 6  7 8
    // Characters appear at even indices (2, 4, 6...).

    for (int end_points = 1; end_points < m - 1; end_points++) {
        // Add current index as a new potential center
        cerr << "Insert: " << end_points << endl;
        active_centers.insert(end_points);

        // Remove centers that ended at the previous step (i-1)
        for (int c : expire[end_points - 1]) {
            active_centers.erase(c);
        }

        // We only verify and output for positions that are actual characters.
        // In the sentinel-padded string "^#a#...", characters are at even indices.
        if (end_points % 2 == 0) {
            int left_most_center = *active_centers.begin();
            // The magic formula (i - center + 1) correctly calculates the length
            // of the palindrome suffix for both odd and even length palindromes
            // due to the properties of the interleaved string.
            cout << (end_points - left_most_center + 1) << " ";
        }
    }
    cout << endl;

    return 0;
}
