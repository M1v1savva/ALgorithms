#include <bits/stdc++.h>

#define int __int64
#define pii pair<int, int>
#define pcc pair<char, char>
#define pb push_back
#define ff first
#define ss second
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define forn(i, x) for(int i = 0; i < x; i++)
#define rforn(i, x) for(int i = x - 1; i >= 0; i--)

using namespace std;

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize("fast-math")

const int INF = 1e9 + 7;

struct Matrix
{
    int rows, cols;
    vector<vector<int> > m;

    Matrix () {}

    Matrix (int _rows, int _cols)
    {
        rows = _rows;
        cols = _cols;
        m = vector<vector<int> >(rows, vector<int>(cols, 0));
    }

    Matrix& operator = (const Matrix &r)
    {
        rows = r.rows;
        cols = r.cols;
        m = r.m;
        return *this;
    }

    Matrix operator * (const Matrix &r)
    {
        Matrix ans(rows, r.cols);

        forn (i, rows)
        {
            forn (j, r.cols)
            {
                forn (k, cols)
                {
                    ans.m[i][j] = (ans.m[i][j] + (m[i][k] * r.m[k][j]) % INF) % INF;
                }
            }
        }

        return ans;
    }

    void print()
    {
        forn (i, rows)
        {
            forn (j, cols)
                cout << m[i][j] << ' ';
            cout << endl;
        }
    }
};

Matrix bin_pow(Matrix a, int p)
{
    if (p == 1)
        return a;
    Matrix res = bin_pow(a * a, p / 2);
    if (p % 2)
        return res * a;
    else
        return res;
}

void solve1(int n, int c)
{
    queue<int> dp;
    int sum = 1;
    forn (i, c)
        dp.push(0);
    dp.push(1);

    for (int i = 0; i < n; i++)
    {
        dp.push(sum);
        sum = (sum - dp.front() + INF) % INF;
        dp.pop();
        sum = (sum + dp.back()) % INF;
    }

    int ans = 0;
    while (dp.size())
    {
        ans = (ans + dp.front()) % INF;
        dp.pop();
    }
    cout << ans;
}

void solve2(int n, int c)
{
    Matrix s(1, c + 1);
    s.m[0][c] = 1;

    Matrix t(c + 1, c + 1);
    for (int i = 0; i < c; i++)
    {
        t.m[i + 1][i] = 1;
    }
    for (int i = 0; i <= c; i++)
        t.m[i][c] = 1;

    Matrix cur = bin_pow(t, n);

    Matrix res = s * cur;
    int ans = 0;
    for (int i = 0; i <= c; i++)
        ans = (ans + res.m[0][i]) % INF;
    cout << ans;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, c;
    cin >> n >> c;

    if (c <= 50)
        solve2(n, c);
    else
        solve1(n, c);

    return 0;
}
