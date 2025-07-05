#include <iostream>
using namespace std;

int josephus(int n)
{
    if (n == 1)
        return 1;
    if (n % 2 == 0)
        return 2 * josephus(n / 2) - 1;
    else
        return 2 * josephus(n / 2) + 1;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cout << josephus(i) << " ";
    cout << endl;
    return 0;
}