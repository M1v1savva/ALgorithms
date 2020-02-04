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

struct Sparse
{
    int n, logn;
    vector<int> lg;
    vector<vector<int> > mx;

    Sparse (vector<int> &v)
    {
        n = v.size();
        logn = 1;
        while ((1 << logn) <= n)
            logn++;
        logn++;

        lg.resize(n + 1);
        lg[0] = lg[1] = 0;
        for (int i = 2; i <= n; i++)
            lg[i] = lg[i / 2] + 1;

        mx = vector<vector<int> >(n, vector<int>(logn));
        forn (i, n)
            mx[i][0] = v[i];

        for (int l = 0; l < logn - 1; l++)
        {
            for (int i = 0; i < n && i + (1 << l) < n; i++)
            {
                mx[i][l + 1] = min(mx[i][l], mx[i + (1 << l)][l]);
            }
        }
    }

    int rmq(int l, int r)
    {
        int t = lg[r - l + 1];
        return min(mx[l][t], mx[r - (1 << t) + 1][t]);
    }
};

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    forn (i, n)
        cin >> a[i];

    Sparse t(a);

    for (int i = k - 1; i < n; i++)
        cout << t.rmq(i - k + 1, i) << '\n';

    return 0;
}
