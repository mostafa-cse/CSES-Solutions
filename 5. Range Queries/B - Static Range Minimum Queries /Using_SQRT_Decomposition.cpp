#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    int block_size = sqrt(n) + 1;
    vector<int> block_min(block_size, LLONG_MAX);
    for (int i = 0; i < n; i++)
    {
        block_min[i / block_size] = min(block_min[i / block_size], a[i]);
    }
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        l--, r--;
        int ans = LLONG_MAX;
        int start_block = l / block_size, end_block = r / block_size;
        if (start_block == end_block)
        {
            for (int i = l; i <= r; i++)
                ans = min(ans, a[i]);
        }
        else
        {
            for (int i = l, end = (start_block + 1) * block_size - 1; i <= end; i++)
                ans = min(ans, a[i]);
            for (int b = start_block + 1; b < end_block; b++)
                ans = min(ans, block_min[b]);
            for (int i = end_block * block_size; i <= r; i++)
                ans = min(ans, a[i]);
        }
        cout << ans << '\n';
    }
    return 0;
}
