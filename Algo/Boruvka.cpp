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

int timer = 0;
vector<vector<int> > g;
vector<int> comp;
vector<bool> used;

void dfs(int v)
{
    comp[v] = timer;
    used[v] = true;
    for (int to : g[v])
        if (!used[to])
            dfs(to);
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector<vector<int> > edges;
    g.resize(n);
    comp.resize(n);
    forn (i, m)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        edges.pb({a, b, c, i});
    }

    vector<bool> appended(m, false);
    while (true)
    {
        used.assign(n, false);
        timer = 0;
        forn (i, n)
        {
            if (!used[i])
            {
                dfs(i);
                timer++;
            }
        }
        if (timer == 1)
            break;
        vector<int> e_min(timer, INF);
        vector<int> edge(timer, -1);

        forn (i, m)
        {
            int a = edges[i][0], b = edges[i][1], c = edges[i][2];
            if (comp[a] != comp[b])
            {
                if (e_min[comp[a]] > c)
                {
                    e_min[comp[a]] = c;
                    edge[comp[a]] = i;
                }
                if (e_min[comp[b]] > c)
                {
                    e_min[comp[b]] = c;
                    edge[comp[b]] = i;
                }
            }
        }

        forn (i, timer)
        {
            int id = edge[i];
            int a = edges[id][0], b = edges[id][1], numb = edges[id][3];
            g[a].pb(b);
            g[b].pb(a);
            appended[numb] = true;
        }
    }
    int ans = 0;
    forn (i, m)
        if (appended[i])
            ans += edges[i][2];
    cout << ans;
    return 0;
}
