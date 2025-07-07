#include <bits/stdc++.h>
using namespace std;

int n, k, sum[200005 << 2];

void push_up(int now)
{
    sum[now] = sum[now << 1] + sum[(now << 1) | 1];
}

void build(int now, int l, int r)
{
    if (l == r)
    {
        sum[now] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(now << 1, l, mid);
    build((now << 1) | 1, mid + 1, r);
    push_up(now);
}

void modify(int now, int l, int r, int pos, int val)
{
    if (l == r)
    {
        sum[now] = val;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        modify(now << 1, l, mid, pos, val);
    else
        modify((now << 1) | 1, mid + 1, r, pos, val);
    push_up(now);
}

int query(int now, int l, int r, int s)
{
    if (l == r)
        return (s == 0 ? l - 1 : l);
    int mid = (l + r) >> 1;
    if (sum[now << 1] < s)
        return query((now << 1) | 1, mid + 1, r, s - sum[now << 1]);
    else
        return query(now << 1, l, mid, s);
}

signed main()
{
    cin >> n >> k;
    build(1, 1, n);
    int t = n, now = 1;
    for (int i = 1; i <= n; i++)
    {
        now = (now + k - 1) % t + 1;
        t--;
        int pos = query(1, 1, n, now);
        cout << pos << ' ';
        modify(1, 1, n, pos, 0);
    }
    return 0;
}