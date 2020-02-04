#include <bits/stdc++.h>

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
#define print(x) for(auto it : x) cout << it << " "; cout << endl;

using namespace std;

int n, m;
vector<vector<char> > a;

const int q1 = 331;

const int MOD1 = 1e9 + 7;

vector<int> power1(n);
vector<vector<vector<int> > > pref;

vector<int> operator - (const vector<int> &a, const vector<int> &b)
{
    vector<int> ans(26, 0);
    forn (i, 26)
        ans[i] = a[i] - b[i];
    return ans;
}

int get(vector<int> &v)
{
    int l = 0, r = -1;
    int n = sz(v);

    vector<int> d1(n, -1);
    forn (i, n)
    {
        int k = 0;
        if (i <= r)
            k = max(r - i, d1[l + r - i]);

        while (i - k > 0 && i + k < n - 1 && v[i - k - 1] == v[i + k + 1])
            k++;

        d1[i] = k;
        if (i + k > r)
        {
            r = i + k;
            l = i - k;
        }
    }

    l = 0;
    r = -1;
    vector<int> d2(n, -1);
    for (int i = 1; i < n; i++)
    {
        if (v[i] != v[i - 1])
            continue;

        int k = 0;
        if (i <= r)
            k = max(r - i, d2[l + r - i]);

        while (i - 1 - k > 0 && i + k < n - 1 && v[i - 1 - k - 1] == v[i + k + 1])
            k++;

        d2[i] = k;
        if (i + k > r)
        {
            r = i + k;
            l = i - 1 - k;
        }
    }

    int res = 0;

    forn (i, n)
        res += d1[i] + 1;
    forn (i, n)
        if (d2[i] != -1)
            res += d2[i] + 1;
    return res;
}

int solve(int l, int r)
{
    vector<int> hs(n);

    vector<bool> satisf(n);

    forn (i, n)
    {
        vector<int> kek = pref[i][r + 1] - pref[i][l];

        int lol = 0;
        forn (j, 26)
            if (kek[j] % 2)
                lol++;

        satisf[i] = (((lol == 1) && ((r - l + 1) % 2 == 1)) || ((lol == 0) && ((r - l + 1) % 2 == 0)));

        int hashes = 0;
        forn (j, 26)
            hashes = ((1ll * hashes * q1) % MOD1 + kek[j] + 1) % MOD1;
        hs[i] = hashes;
    }

    vector<int> cur;
    int ans = 0;
    forn (i, n)
    {
        if (satisf[i])
            cur.pb(hs[i]);
        else
        {
            if (sz(cur))
            {
                ans += get(cur);
                cur.clear();
            }
        }
    }
    if (sz(cur))
        ans += get(cur);

    return ans;
}

signed main()
{
    //freopen("test.txt", "r", stdin);

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    a = vector<vector<char> > (n, vector<char>(m));
    forn (i, n)
        forn (j, m)
            cin >> a[i][j];

    power1.resize(350);
    power1[0] = 1;
    forn (i, 350 - 1)
        power1[i + 1] = (1ll * power1[i] * q1) % MOD1;

    pref = vector<vector<vector<int> > > (n, vector<vector<int> >(m + 1, vector<int>(26, 0)));

    forn (i, n)
    {
        forn (j, m)
        {
            pref[i][j + 1] = pref[i][j];
            pref[i][j + 1][a[i][j] - 'a']++;
        }
    }

    int ans = 0;
    forn (l, m)
    {
        for (int r = l; r < m; r++)
        {
            ans += solve(l, r);
        }
    }

    cout << ans;
    return 0;
}
