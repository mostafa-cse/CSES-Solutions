#include <bits/stdc++.h>
using namespace std;
struct BIT
{
    int N;
    vector<int> f;
    BIT(int n) : N(n), f(n + 1, 0) {}
    void update(int i, int v)
    {
        for (; i <= N; i += i & -i)
            f[i] = max(f[i], v);
    }
    int query(int i)
    {
        int r = 0;
        for (; i > 0; i -= i & -i)
            r = max(r, f[i]);
        return r;
    }
};
int solve_bit(vector<pair<int, int>> I)
{
    int n = I.size();
    vector<int> xs;
    for (auto &iv : I)
    {
        xs.push_back(iv.first);
        xs.push_back(iv.second);
    }
    sort(xs.begin(), xs.end());

    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    for (auto &iv : I)
    {
        iv.first = lower_bound(xs.begin(), xs.end(), iv.first) - xs.begin() + 1;
        iv.second = lower_bound(xs.begin(), xs.end(), iv.second) - xs.begin() + 1;
    }
    sort(I.begin(), I.end(), [](auto &a, auto &b)
         { return a.second < b.second; });
    BIT bit(xs.size());
    for (auto &iv : I)
    {
        int best = bit.query(iv.first);
        bit.update(iv.second, best + 1);
    }
    return bit.query(xs.size());
}

int main()
{
    int n;
    cin >> n;

    vector<pair<int, int>> I(n);
    for (int i = 0; i < n; i++)
    {
        cin >> I[i].first >> I[i].second;
    }
    cout << solve_bit(I);
    return 0;
}