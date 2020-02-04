#include <bits/stdc++.h>

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

int timer;
vector<vector<int> > g;
vector<int> tin, path, first, id;

void dfs(int v)
{
    tin[v] = timer++;
    id[tin[v]] = v;

    path.pb(tin[v]);
    first[tin[v]] = path.size() - 1;
    for (int to : g[v])
    {
        dfs(to);
        path.pb(tin[v]);
    }
}

int n, logn;
vector<int> lg;
vector<vector<int> > mx;

void build()
{
    dfs(0);

    logn = 1;
    while ((1 << logn) <= path.size())
        logn++;
    logn++;

    lg.resize(path.size() + 1);
    lg[0] = lg[1] = 0;
    for (int i = 2; i <= path.size(); i++)
        lg[i] = lg[i / 2] + 1;

    mx = vector<vector<int> >(path.size(), vector<int>(logn));

    forn (i, path.size())
        mx[i][0] = path[i];

    forn (l, logn - 1)
        for (int i = 0; (i < path.size()) && (i + (1 << l) < path.size()); i++)
            mx[i][l + 1] = min(mx[i][l], mx[i + (1 << l)][l]);
}

int rmq(int l, int r)
{
    int t = lg[r - l + 1];
    return min(mx[l][t], mx[r - (1 << t) + 1][t]);
}

int lca(int a, int b)
{
    int t1 = tin[a];
    int t2 = tin[b];
    if (t1 > t2)
        swap(t1, t2);

    int l = first[t1];
    int r = first[t2];

    return id[rmq(l, r)];
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

    timer = 0;
    n = edges.size() + 1;
    g.resize(n);
    tin.resize(n);
    id.resize(n);
    first.assign(n, -1);

    forn (i, edges.size())
        g[edges[i].ff].pb(edges[i].ss);

    build();

    forn (i, query.size())
        cout << lca(query[i].ff, query[i].ss) + 1 << '\n';
    return 0;
}
