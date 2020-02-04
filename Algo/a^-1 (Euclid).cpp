#include <bits/stdc++.h>

#define int long long
#define pii pair<int, int>
#define pb push_back
#define ff first
#define ss second
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define forn(i, x) for (int i = 0; i < x; i++)
#define rforn(i, n) for (int i = x - 1; i >= 0; i--)
#define print(x) forn (i, (x).size()) cout << x[i] << ' '; cout << '\n';

using namespace std;

int gcd(int a, int b)
{
    return (b ? gcd(b, a % b) : a);
}

pii solve(int a, int b)
{
    if (a == 0)
        return pii(0, 1);

    pii ans = solve(b % a, a);
    int g = gcd(b % a, a);
    int x1 = ans.ff, y1 = ans.ss;

    int x = y1 - (b / a) * x1;
    int y = x1;
    return {x, y};
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int a, m;
    cin >> a >> m;

    if (gcd(a, m) != 1)
    {
        cout << 0;
        return 0;
    }

    pii ans = solve(a, m);
    cout << (ans.ff % m + m) % m;
    return 0;
}
