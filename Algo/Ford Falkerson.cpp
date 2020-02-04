#include <bits/stdc++.h>

#define int long long
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
    int to, f, c;

    edge(int _to, int _f, int _c)
    {
        to = _to;
        f = _f;
        c = _c;
    }
};

int n, m, S, T;

vector<bool> used;
vector<vector<int> > g;
vector<edge> e;

bool dfs(int v)
{
    if (used[v])
        return false;
    used[v] = true;

    if (v == T)
        return true;

    for (int id : g[v])
    {
        int to = e[id].to, f = e[id].f, c = e[id].c;

        if (c - f == 0)
            continue;

        bool ans = dfs(to);
        if (ans)
        {
            e[id].f++;
            e[id ^ 1].f = -e[id].f;
            return true;
        }
    }

    return false;
}

bool find_max_flow()
{
    used.assign(n, false);
    bool ok = dfs(S);
    if (!ok)
        return false;

    used.assign(n, false);
    ok = dfs(S);
    if (!ok)
        return false;

    return true;
}

signed main()
{
    //freopen("test.txt", "r", stdin);

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> S >> T;
    S--;
    T--;

    g.resize(n);
    forn (i, m)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].pb(sz(e));
        e.pb(edge(b, 0, 1));
        g[b].pb(sz(e));
        e.pb(edge(a, 0, 0));
    }

    bool ok = find_max_flow();

    if (!ok)
    {
        cout << "NO";
        return 0;
    }

    vector<vector<int> > nxt(n);

    forn (v, n)
    {
        for (int x : g[v])
        {
            if (e[x].f == 1)
                nxt[v].pb(e[x].to);
        }
    }

    cout << "YES" << endl;
    for (int cur = S;;)
    {
        cout << cur + 1 << ' ';
        if (cur == T)
            break;

        int to = nxt[cur].back();
        nxt[cur].pop_back();
        cur = to;
    }
    cout << endl;

    for (int cur = S;;)
    {
        cout << cur + 1 << ' ';
        if (cur == T)
            break;

        int to = nxt[cur].back();
        nxt[cur].pop_back();
        cur = to;
    }

    return 0;
}
