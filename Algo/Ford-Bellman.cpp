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

const int INF = 1e9 + 7;

struct edge
{
    int a, b, c;
    edge (int _a, int _b, int _c) : a(_a), b(_b), c(_c) {}
};

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<vector<int> > g(n, vector<int>(n));
    vector<edge> edges;

    forn (i, n)
    {
        forn (j, n)
        {
            cin >> g[i][j];
            if (g[i][j] != 100000)
                edges.pb(edge(i, j, g[i][j]));
        }
    }

    vector<int> d(n, 0);
    d[0] = 0;
    vector<int> p(n, -1);

    int x = -1;
    forn (i, n)
    {
        x = -1;
        forn (j, edges.size())
        {
            int a = edges[j].a, b = edges[j].b, c = edges[j].c;
            if (d[b] > d[a] + c)
            {
                d[b] = d[a] + c;
                p[b] = a;
                x = b;
            }
        }
    }

    if (x == -1)
    {
        cout << "NO";
        return 0;
    }

    forn (i, n)
        x = p[x];

    vector<int> ans;
    ans.pb(x + 1);
    int x0 = x;
    x = p[x];
    while (x != x0)
    {
        ans.pb(x + 1);
        x = p[x];
    }
    ans.pb(x + 1);
    reverse(all(ans));

    cout << "YES" << '\n';
    cout << ans.size() << '\n';
    print(ans);
    return 0;
}
