#include <bits/stdc++.h>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("unswitch-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("profile-values")
#pragma GCC optimize("tracer")
#pragma GCC optimize("vpt")
#pragma GCC optimize("rename-registers")
#pragma GCC optimize("move-loop-invariants")
#pragma GCC optimize("function-sections")
#pragma GCC optimize("data-sections")
#pragma GCC optimize("branch-target-load-optimize")
#pragma GCC optimize("branch-target-load-optimize2")
#pragma GCC optimize("btr-bb-exclusive")
#pragma GCC target("sse2")
#pragma GCC target("sse3")
#pragma GCC target("ssse3")
#pragma GCC target("sse4.1")
#pragma GCC target("sse4.2")
#pragma GCC target("avx")
#pragma GCC target("avx2")
#pragma GCC target("popcnt")
#pragma GCC target("abm")
#pragma GCC target("mmx")
#pragma GCC target("tune=native")

#define ll long long
#define pii pair<int, int>
#define pb push_back
#define ff first
#define ss second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define forn(i, x) for(int i = 0; i < x; i++)
#define rforn(i, x) for(int i = x - 1; i >= 0; i--)
#define printp(x) for(int i = 0; i < (x).size(); i++) cout << (x)[i] + 1 << " "; cout << endl;
#define print(x) for(int i = 0; i < (x).size(); i++) cout << (x)[i] << " "; cout << endl;

using namespace std;

struct edge
{
    int v, to, f, c, cost;
};

const int INF = numeric_limits<int>::max();

int n, m, S, T;

vector<edge> e;
vector<int> d, path;
vector<pii> p;

bool ford_bellman()
{
    forn (i, n)
        d[i] = 0;

    forn (i, n)
        p[i] = {-1, -1};

    int x = -1;
    forn (i, n)
    {
        x = -1;
        forn (j, m * 2)
        {
            int v = e[j].v, to = e[j].to, cost = e[j].cost;

            if (e[j].c - e[j].f == 0)
                continue;

            if (d[to] > d[v] + cost)
            {
                d[to] = d[v] + cost;
                p[to] = {v, j};
                x = to;
            }
        }
    }

    if (x == -1)
        return false;

    forn (i, n)
        x = p[x].ff;

    bool ok = false;
    path.clear();
    for (int to = x; !ok || to != x; to = p[to].ff)
    {
        ok = true;
        path.pb(p[to].ss);
    }
    return true;
}

void update()
{
    int minC = INF;

    for (int id : path)
        minC = min(minC, e[id].c - e[id].f);

    for (int id : path)
    {
        e[id].f += minC;
        e[id ^ 1].f = -e[id].f;
    }
}

vector<vector<int> > g;

bool bfs()
{
    forn (i, n)
        d[i] = INF;
    d[S] = 0;
    forn (i, n)
        p[i] = {-1, -1};

    queue<int> q;
    q.push(S);
    while (sz(q))
    {
        int v = q.front();
        q.pop();

        for (int id : g[v])
        {
            int to = e[id].to, f = e[id].f, c = e[id].c;

            if (c - f > 0 && d[to] == INF && d[to] > d[v] + 1)
            {
                d[to] = d[v] + 1;
                p[to] = {v, id};
                q.push(to);
            }
        }
    }

    if (d[T] == INF)
        return false;

    path.clear();
    for (int cur = T; p[cur].ss != -1; cur = p[cur].ff)
        path.pb(p[cur].ss);
    return true;
}

void find_max_flow()
{
    while (bfs())
        update();
}

ll min_cost_max_flow()
{
    find_max_flow();

    while (ford_bellman())
        update();

    ll min_cost = 0;
    for (int i = 0; i < m * 2; i += 2)
        min_cost += 1ll * e[i].cost * e[i].f;

    return min_cost;
}

signed main()
{
    //freopen("test.txt", "r", stdin);

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    S = 0;
    T = n - 1;
    d.resize(n);
    p.resize(n);
    g.resize(n);

    forn (i, m)
    {
        int a, b, c, cost;
        cin >> a >> b >> c >> cost;
        a--;
        b--;
        g[a].pb(sz(e));
        e.pb({a, b, 0, c, cost});
        g[b].pb(sz(e));
        e.pb({b, a, 0, 0, -cost});
    }

    cout << min_cost_max_flow();
    return 0;
}
