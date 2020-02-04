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

int lg;
int timer = 0;

vector<vector<int> > g, up;
vector<bool> used;
vector<int> tin, tout;

void build(int v, int p)
{
    tin[v] = timer++;

    up[v][0] = p;
    for (int l = 0; l < lg; l++)
        up[v][l + 1] = up[up[v][l]][l];

    for (int to : g[v])
        build(to, v);

    tout[v] = timer++;
}

bool upper(int a, int b)
{
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b)
{
    if (upper(a, b))
        return a;
    if (upper(b, a))
        return b;

    for (int l = lg; l >= 0; l--)
        if (!upper(up[a][l], b))
            a = up[a][l];
    return up[a][0];
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int m;
    cin >> m;
    vector<pii> edges, query;
    forn (i, m)
    {
        string s;
        int a, b;
        cin >> s;
        cin >> a >> b;
        a--;
        b--;
        if (s == "ADD")
            edges.pb({a, b});
        else
            query.pb({a, b});
    }

    int n = edges.size() + 1;
    g.resize(n);
    tout.resize(n);
    tin.resize(n);

    forn (i, edges.size())
        g[edges[i].ff].pb(edges[i].ss);

    lg = 1;
    while ((1 << lg) <= n)
        lg++;

    up = vector<vector<int> >(n, vector<int>(lg + 1));
    build(0, 0);

    forn (i, query.size())
        cout << lca(query[i].ff, query[i].ss) + 1 << '\n';
    return 0;
}
