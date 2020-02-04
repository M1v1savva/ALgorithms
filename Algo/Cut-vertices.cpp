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
vector<vector<int> > g;
vector<bool> used, ans;
vector<int> tin, fup;

void dfs(int v, int p)
{
    used[v] = true;
    tin[v] = fup[v] = timer++;

    int children = 0;
    for (int to : g[v])
    {
        if (to == p)
            continue;
        if (used[to])
            fup[v] = min(fup[v], tin[to]);
        else
        {
            dfs(to, v);
            children++;
            fup[v] = min(fup[v], fup[to]);
            if (fup[to] >= tin[v] && v != p)
                ans[v] = true;
        }
    }

    if (children > 1 && v == p)
        ans[v] = true;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    g.resize(n);
    used.assign(n, false);
    ans.assign(n, false);
    tin.resize(n);
    fup.resize(n);

    forn (i, m)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].pb(b);
        g[b].pb(a);
    }

    forn (i, n)
    {
        if (!used[i])
            dfs(i, i);
    }

    vector<int> res;
    forn (i, n)
        if (ans[i])
            res.pb(i);

    cout << res.size() << '\n';
    for (int x : res)
        cout << ++x << '\n';
    return 0;
}
