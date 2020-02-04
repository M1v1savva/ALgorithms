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

int timer = 0;
vector<vector<pii> > g;
vector<bool> used, ans;
vector<int> tin, fup;

void dfs(int v, int p = -1)
{
    used[v] = true;
    tin[v] = fup[v] = timer++;
    forn (i, g[v].size())
    {
        int to = g[v][i].ff, id = g[v][i].ss;
        if (to == p || to == v)
            continue;
        if (used[to])
            fup[v] = min(fup[v], tin[to]);
        else
        {
            dfs(to, v);
            fup[v] = min(fup[v], fup[to]);
            if (fup[to] > tin[v])
                ans[id] = true;
        }
    }
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    g.resize(n);
    tin.resize(n);
    fup.resize(n);
    used.assign(n, false);
    ans.assign(m, false);

    vector<pii> edges;
    map<pii, int> data;

    forn (i, m)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].pb(pii(b, i));
        g[b].pb(pii(a, i));
        data[{a, b}]++;
        data[{b, a}]++;
        edges.pb({a, b});
    }

    forn (i, n)
    {
        if (!used[i])
            dfs(i);
    }

    vector<int> res;
    forn (i, m)
        if (ans[i] && data[edges[i]] == 1)
            res.pb(i);

    cout << res.size() << '\n';
    for (int x : res)
        cout << ++x << '\n';
    return 0;
}
