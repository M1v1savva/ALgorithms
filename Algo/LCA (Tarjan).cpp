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
vector<vector<pii> > query;
vector<int> ans;
vector<bool> used;

vector<int> p, r, root;

int find(int a)
{
    if (p[a] == a)
        return a;
    return p[a] = find(p[a]);
}

void unite(int a, int b)
{
    int b0 = b;
    a = find(a);
    b = find(b);
    if (a != b)
    {
        if (r[a] > r[b])
            swap(a, b);
        p[a] = b;
        root[b] = b0;
        if (r[a] == r[b])
            r[b]++;
    }
}

void dfs(int v)
{
    used[v] = true;

    for (int to : g[v])
    {
        dfs(to);
        unite(to, v);
    }

    forn (i, query[v].size())
    {
        int to = query[v][i].ff, id = query[v][i].ss;
        if (used[to])
            ans[id] = root[find(to)];
    }
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int m;
    cin >> m;
    vector<pii> edges, q;
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
            q.pb({a, b});
    }

    int n = edges.size() + 1;
    g.resize(n);
    query.resize(n);
    ans.resize(q.size());

    forn (i, edges.size())
        g[edges[i].ff].pb(edges[i].ss);

    forn (i, q.size())
    {
        int a = q[i].ff, b = q[i].ss;
        query[a].pb({b, i});
        query[b].pb({a, i});
    }

    p.resize(n);
    r.resize(n);
    root.resize(n);
    used.assign(n, false);
    forn (i, n)
    {
        p[i] = i;
        root[i] = i;
        r[i] = 1;
    }

    dfs(0);

    forn (i, ans.size())
        cout << ++ans[i] << '\n';
    return 0;
}
