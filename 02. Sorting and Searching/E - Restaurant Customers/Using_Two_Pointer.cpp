#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int arrival[n], departure[n];
    for (int i = 0; i < n; ++i)
    {
        cin >> arrival[i] >> departure[i];
    }

    sort(arrival, arrival + n);
    sort(departure, departure + n);

    int current_customers = 0, max_customers = 0;
    int i = 0, j = 0;

    while (i < n && j < n)
    {
        if (arrival[i] < departure[j])
        {
            current_customers++;
            i++;
            max_customers = max(max_customers, current_customers);
        }
        else
        {
            current_customers--;
            j++;
        }
    }

    cout << max_customers << '\n';

    return 0;
}