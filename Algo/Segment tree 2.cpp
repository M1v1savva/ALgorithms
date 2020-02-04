#include <bits/stdc++.h>

#define int long long
#define pii pair<int, int>
#define pcc pair<char, char>
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

const int INF = 1e9;

int lg;
int timer = 0, timer_for_seg = 0;

vector<vector<int> > g, up;
vector<bool> used;
vector<int> tin_for_seg, tin, tout, id, d;

void build(int v, int p, int depth = 0)
{
    tin[v] = timer++;
    tin_for_seg[v] = timer_for_seg++;
    d[v] = depth;
    id[tin_for_seg[v]] = v;

    up[v][0] = p;
    for (int l = 0; l < lg; l++)
        up[v][l + 1] = up[up[v][l]][l];

    for (int to : g[v])
        build(to, v, depth + 1);

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

vector<vector<int> > t;

void build_seg(int v, int tl, int tr)
{
    if (tl == tr)
    {
        t[v][0] = t[v][2] = tin_for_seg[tl];
        t[v][1] = INF;
        t[v][3] = -INF;
    }
    else
    {
        int tm = (tl + tr) / 2;
        build_seg(v * 2 + 1, tl, tm);
        build_seg(v * 2 + 2, tm + 1, tr);

        vector<int> v1 = t[v * 2 + 1];
        vector<int> v2 = t[v * 2 + 2];

        vector<int> mn = {v1[0], v1[1], v2[0], v2[1]};
        vector<int> mx = {v1[2], v1[3], v2[2], v2[3]};
        sort(all(mn));
        sort(rall(mx));

        t[v][0] = mn[0];
        t[v][1] = mn[1];

        t[v][2] = mx[0];
        t[v][3] = mx[1];
    }
}

vector<int> get(int v, int tl, int tr, int l, int r)
{
    if (l > r)
        return {INF, INF, -INF, -INF};
    if (tl == l && tr == r)
        return t[v];

    int tm = (tl + tr) / 2;
    vector<int> v1 = get(v * 2 + 1, tl, tm, l, min(r, tm));
    vector<int> v2 = get(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r);

    vector<int> mn = {v1[0], v1[1], v2[0], v2[1]};
    vector<int> mx = {v1[2], v1[3], v2[2], v2[3]};
    sort(all(mn));
    sort(rall(mx));

    vector<int> ans(4);

    ans[0] = mn[0];
    ans[1] = mn[1];

    ans[2] = mx[0];
    ans[3] = mx[1];

    return ans;
}

signed main()
{
    //freopen("test.txt", "r", stdin);

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;
    g.resize(n);

    forn (i, n - 1)
    {
        int p;
        cin >> p;
        g[p - 1].pb(i + 1);
    }

    used.assign(n, false);
    tin.resize(n);
    tout.resize(n);
    id.resize(n);
    d.resize(n);
    tin_for_seg.resize(n);

    lg = 0;
    while ((1 << lg) <= n)
        lg++;
    lg++;

    up = vector<vector<int> >(n, vector<int>(lg + 1));

    build(0, 0);

    t = vector<vector<int> >(n * 4, vector<int>(4));
    build_seg(0, 0, n - 1);

    forn (i, q)
    {
        int l, r;
        cin >> l >> r;
        l--;
        r--;

        vector<int> v = get(0, 0, n - 1, l, r);

        int lca1 = lca(id[v[1]], id[v[2]]);
        int lca2 = lca(id[v[0]], id[v[3]]);

        if (d[lca1] > d[lca2])
            cout << id[v[0]] + 1 << ' ' << d[lca1] << endl;
        else
            cout << id[v[2]] + 1 << ' ' << d[lca2] << endl;
    }

    return 0;
}
