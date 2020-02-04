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

const int INF = 1e18 + 7;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<pii> > g(n);
    forn (i, m)
    {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].pb({b, c});
        g[b].pb({a, ñ});
    }
    int st;
    cin >> st;

    vector<int> d(n, INF);
    d[st] = 0;
    set<pii> s;
    s.insert({d[st], st});

    while (s.size())
    {
        int v = s.begin()-> ss;
        s.erase(s.begin());

        forn (i, g[v].size())
        {
            int to = g[v][i].ff, cost = g[v][i].ss;
            if (d[to] > d[v] + cost)
            {
                s.erase({d[to], to});
                d[to] = d[v] + cost;
                s.insert({d[to], to});
            }
        }
    }
    forn (i, n)
    {
        cout << (d[i] >= INF ? 2009000999 : d[i]) << ' ';
    }
    cout << endl;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    forn (i, t)
        solve();

    return 0;
}
