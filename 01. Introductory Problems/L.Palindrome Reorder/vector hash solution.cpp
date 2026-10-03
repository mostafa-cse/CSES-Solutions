#include<bits/stdc++.h>
using namespace std;
 
int32_t main(){
    string str;
    cin >> str;

    vector<int> hsh(27, 0);
    string left = "", right = "";
    for (int i = 0; i < str.size(); i++) {
        hsh[str[i] - 'A']++;
    }

    int ok = 0;
    for (int i = 0; i < 27; i++) {
        if (hsh[i] % 2) {
            ok++;
        }
    }

    if (ok >= 2) {
        cout << "NO SOLUTION" << '\n';
        return 0;
    }

    char oddChar = ' ';
    for (int i = 0; i < 27; i++) {
        if (hsh[i] & 1) {
            oddChar = i + 'A';
        }
        for (int j = 0; j < hsh[i] - 1; j += 2) {
            left += (i + 'A');
            right += (i + 'A');
        }
    }
    reverse(right.begin(),right.end());

    if (oddChar != ' ') {
        left += oddChar;
    }
    cout << left + right << '\n';
    return 0;
}