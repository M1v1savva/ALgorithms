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

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin >> s;
    vector<int> f(s.size(), 0);
    for (int i = 1; i < s.size(); i++)
    {
        int j = f[i - 1];
        while (j > 0 && s[j] != s[i])
            j = f[j - 1];
        if (s[j] == s[i])
            j++;
        f[i] = j;
    }

    print(f);
    return 0;
}
