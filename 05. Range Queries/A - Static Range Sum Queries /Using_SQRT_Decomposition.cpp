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
    vector<int> block_sum(block_size, 0);
    for (int i = 0; i < n; i++)
    {
        block_sum[i / block_size] += a[i];
    }
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        l--, r--;
        int sum = 0;
        int start_block = l / block_size, end_block = r / block_size;
        if (start_block == end_block)
        {
            for (int i = l; i <= r; i++)
                sum += a[i];
        }
        else
        {
            for (int i = l, end = (start_block + 1) * block_size - 1; i <= end; i++)
                sum += a[i];
            for (int b = start_block + 1; b < end_block; b++)
                sum += block_sum[b];
            for (int i = end_block * block_size; i <= r; i++)
                sum += a[i];
        }
        cout << sum << '\n';
    }
    return 0;
}
