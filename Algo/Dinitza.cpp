#include <bits/stdc++.h>

#define ll long long
#define pii pair<int, int>
#define pb push_back
#define ff first
#define ss second
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()
#define forn(i, x) for(int i = 0; i < x; i++)
#define rforn(i, x) for(int i = x - 1; i >= 0; i--)
#define printp(x) for(int i = 0; i < (x).size(); i++) cout << (x)[i] + 1 << " "; cout << endl;
#define print(x) for(int i = 0; i < (x).size(); i++) cout << (x)[i] << " "; cout << endl;

using namespace std;

struct edge
{
    int to, f, c;
};

const ll INF = 1e9 + 9;

int n, m, S, T;

vector<edge> e;
vector<vector<int> > g;
vector<int> d, p;

bool bfs(int scale)
{
    queue<int> q;
    forn (i, n)
        d[i] = INF;
    d[S] = 0;
    q.push(S);

    while (sz(q))
    {
        int v = q.front();
        q.pop();

        for (int id : g[v])
        {
            int to = e[id].to, f = e[id].f, c = e[id].c;

            if (c - f >= scale && d[to] == INF)
            {
                d[to] = d[v] + 1;
                q.push(to);
            }
        }
    }

    return (d[T] != INF);
}

int dfs(int v, int minC, int scale)
{
    if (v == T)
        return minC;

    for (int i = p[v]; i < sz(g[v]); i++)
    {
        int id = g[v][i];
        int to = e[id].to, f = e[id].f, c = e[id].c;

        if (c - f >= scale && d[to] == d[v] + 1)
        {
            int ans = dfs(to, min(c - f, minC), scale);

            if (ans)
            {
                e[id].f += ans;
                e[id ^ 1].f = -e[id].f;
                return ans;
            }
        }

        p[v]++;
    }

    return 0;
}

ll find_max_flow()
{
    ll max_flow = 0;

    int scale = 1 << 30;
    while (scale)
    {
        while (bfs(scale))
        {
            forn (i, n)
                p[i] = 0;

            int flow = 1;
            while (flow)
            {
                flow = dfs(S, INF, scale);
                max_flow += flow;
            }
        }
        scale /= 2;
    }
    return max_flow;
}

signed main()
{
    //freopen("test.txt", "r", stdin);

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    g.resize(n);
    d.resize(n);
    p.resize(n);
    S = 0;
    T = n - 1;

    forn (i, m)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        g[a].pb(sz(e));
        e.pb({b, 0, c});
        g[b].pb(sz(e));
        e.pb({a, 0, 0});
    }

    cout << find_max_flow();
    return 0;
}
