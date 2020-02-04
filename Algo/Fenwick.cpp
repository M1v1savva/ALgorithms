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

vector<int> t;

void add(int x, int d)
{
    for (; x <= t.size() - 1; x += x & -x)
        t[x] += d;
}

int get(int x)
{
    int ans = 0;
    for (; x > 0; x -= x & -x)
        ans += t[x];
    return ans;
}

int rsq(int l, int r)
{
    return get(r) - get(l - 1);
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    t.resize(n + 1);
    vector<int> a(n + 1);
    forn (i, n)
    {
        int x;
        cin >> x;
        add(i + 1, x);
        a[i + 1] = x;
    }

    int m;
    cin >> m;
    forn (i, m)
    {
        char c;
        cin >> c;
        if (c == 's')
        {
            int l, r;
            cin >> l >> r;
            cout << rsq(l, r) << ' ';
        }
        else
        {
            int p, x;
            cin >> p >> x;
            add(p, -a[p]);
            a[p] = x;
            add(p, a[p]);
        }
    }

    return 0;
}
