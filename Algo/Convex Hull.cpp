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

struct vec
{
    double x, y;
    vec() {}
    vec(double _x, double _y) : x(_x), y(_y) {}

    vec& operator = (const vec &r)
    {
        x = r.x;
        y = r.y;
        return *this;
    }

    vec operator + (const vec &r)
    {
        return vec(x + r.x, y + r.y);
    }

    vec operator - (const vec &r)
    {
        return vec(x - r.x, y - r.y);
    }

    vec operator * (const int k)
    {
        return vec(x * k, y * k);
    }

    vec operator / (const int k)
    {
        return vec(x / k, y / k);
    }

    double operator * (const vec &r)
    {
        return x * r.x + y * r.y;
    }

    double operator ^ (const vec &r)
    {
        return x * r.y - y * r.x;
    }

    bool operator == (const vec &r)
    {
        return x == r.x && y == r.y;
    }
};

bool cmp(const vec &a, const vec &b)
{
    return (a.x == b.x ? a.y < b.y : a.x < b.x);
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<vec> v(n);
    forn (i, n)
        cin >> v[i].x >> v[i].y;

    sort(all(v), cmp);
    auto it = unique(all(v));
    v.resize(it - v.begin());

    if (v.size() == 1)
    {
        cout << 1 << '\n';
        cout << v[0].x << ' ' << v[0].y;
        return 0;
    }

    int n0 = n;

    n = v.size();
    vector<vec> down, up;
    vec p1 = v[0];
    vec p2 = v[n - 1];
    up.pb(p1);
    down.pb(p1);

    for (int i = 1; i < n; i++)
    {
        if (i == n - 1 || ((v[i] - p1) ^ (p2 - v[i])) < 0)
        {
            while (up.size() > 1 && ((up.back() - up[up.size() - 2]) ^ (v[i] - up.back())) >= 0)
                up.pop_back();
            up.pb(v[i]);
        }
        if (i == n - 1 || ((v[i] - p1) ^ (p2 - v[i])) > 0)
        {
            while (down.size() > 1 && ((down.back() - down[down.size() - 2]) ^ (v[i] - down.back())) <= 0)
                down.pop_back();
            down.pb(v[i]);
        }
    }

    vector<vec> ans;
    forn (i, up.size())
        ans.pb(up[i]);
    for (int i = (int)down.size() - 2; i > 0; i--)
        ans.pb(down[i]);

    if (n0 % 2 == 0)
        reverse(all(ans));

    cout << ans.size() << '\n';
    forn (i, ans.size())
        cout << ans[i].x << ' ' << ans[i].y << '\n';
    return 0;
}
