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

const int INF = 1e18;

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector<vector<pii> > g(n);
    forn (i, m)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        g[a].pb({b, c});
        g[b].pb({a, c});
    }

    vector<int> min_e(n, INF);
    vector<bool> used(n, false);
    min_e[0] = 0;

    int ans = 0;
    forn (i, n)
    {
        int v = -1;
        forn (j, n)
        {
            if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
                v = j;
        }

        used[v] = true;
        if (min_e[v] != INF)
            ans += min_e[v];

        forn (j, g[v].size())
        {
            int to = g[v][j].ff, c = g[v][j].ss;
            if (min_e[to] > c)
                min_e[to] = c;
        }
    }

    cout << ans;
    return 0;
}
