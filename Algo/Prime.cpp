#include <bits/stdc++.h>

#define int long long
#define pii pair<int, int>
#define pb push_back
#define ff first
#define ss second
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define forn(i, x) for (int i = 0; i < (int)x; i++)
#define rforn(i, n) for (int i = (int)x - 1; i >= 0; i--)
#define print(x) forn (i, (x).size()) cout << x[i] << ' '; cout << '\n';

using namespace std;

signed main()
{
    int m, n;
    cin >> m >> n;

    vector<int> lp(n + 1, 0), pr;
    for (int i = 2; i < n + 1; i++)
    {
        if (lp[i] == 0)
        {
            lp[i] = i;
            pr.pb(i);
        }
        for (int j = 0; j < pr.size() && pr[j] <= i && pr[j] * i <= n; j++)
            lp[pr[j] * i] = pr[j];
    }

    vector<int> ans;
    for (int i = m; i <= n; i++)
        if (lp[i] == i)
            ans.pb(i);
    if (ans.empty())
        cout << "Absent";
    else
    {
        for (int x : ans)
            cout << x << '\n';
    }
}
