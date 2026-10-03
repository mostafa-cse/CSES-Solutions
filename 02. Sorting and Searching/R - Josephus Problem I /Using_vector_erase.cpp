#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    list<int> v;
    for (int i = 1; i <= n; i++)
    {
        v.push_back(i);
    }
    auto it = v.begin();
    while (!v.empty())
    {
        ++it;
        if (v.end() == it)
            it = v.begin();
        cout << *it << " ";
        it = v.erase(it);
        if (v.end() == it)
            it = v.begin();
    }
}