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

vector<int> a;
vector<int> t;

void build(int v, int tl, int tr)
{
    if (tl == tr)
        t[v] = a[tl];
    else
    {
        int tm = (tl + tr) / 2;
        build(v * 2 + 1, tl, tm);
        build(v * 2 + 2, tm + 1, tr);
        t[v] = -1;
    }
}

void push(int v)
{
    if (t[v] != -1)
    {
        t[v * 2 + 1] = t[v * 2 + 2] = t[v];
        t[v] = -1;
    }
}

void update(int v, int tl, int tr, int l, int r, int x)
{
    if (l > r)
        return;
    if (tl == l && r == tr)
        t[v] = x;
    else
    {
        push(v);
        int tm = (tl + tr) / 2;
        update(v * 2 + 1, tl, tm, l, min(tm, r), x);
        update(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r, x);
    }
}

int get(int v, int tl, int tr, int pos)
{
    if (tl == tr)
        return t[v];
    push(v);
    int tm = (tl + tr) / 2;
    if (pos <= tm)
        return get(v * 2 + 1, tl, tm, pos);
    else
        return get(v * 2 + 2, tm + 1, tr, pos);
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    a.resize(n);
    forn (i, n)
        cin >> a[i];
    t.resize(n * 4 + 10);
    build(0, 0, n - 1);

    int q;
    cin >> q;
    forn (i, q)
    {
        char c;
        cin >> c;
        if (c == 'g')
        {
            int x;
            cin >> x;
            x--;
            cout << get(0, 0, n - 1, x) << ' ';
        }
        else
        {
            int l, r, x;
            cin >> l >> r >> x;
            l--; r--;
            update(0, 0, n - 1, l, r, x);
        }
    }
    return 0;
}
