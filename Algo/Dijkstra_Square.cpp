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

const int INF = 1e9 + 7;

void solve()
{
    int n, s, t;
    cin >> n >> s >> t;
    s--; t--;
    vector<vector<int> > g(n, vector<int>(n));
    forn (i, n)
    {
        forn (j, n)
        {
            cin >> g[i][j];
            if (g[i][j] <= 0)
                g[i][j] = INF;
        }
    }

    vector<int> d(n, INF);
    d[s] = 0;
    vector<bool> used(n, false);

    forn (i, n)
    {
        int v = -1;
        forn (j, n)
            if (!used[j] && (v == -1 || d[j] < d[v]))
                v = j;

        if (v == -1)
            break;

        used[v] = true;
        forn (i, n)
        {
            int to = i, cost = g[v][i];
            d[to] = min(d[to], d[v] + cost);
        }
    }

    cout << (d[t] >= INF ? -1 : d[t]);
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    solve();

    return 0;
}
