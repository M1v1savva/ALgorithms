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

struct node
{
    vector<node*> go;
    int term;

    node()
    {
        go.assign(26, nullptr);
        term = 0;
    }
};

void add(node* p, string &s, int pos)
{
    if (pos == s.size())
    {
        p-> term++;
        return;
    }

    if (p-> go[s[pos] - 'a'] == nullptr)
        p-> go[s[pos] - 'a'] = new node();
    add(p-> go[s[pos] - 'a'], s, pos + 1);
}

int get(node* p)
{
    int res = 0;
    forn (i, 26)
        if (p-> go[i])
            res = max(res, get(p-> go[i]));
    if (p-> term)
        res++;
    return res;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    node* root = new node();

    int n;
    cin >> n;
    forn (i, n)
    {
        string s;
        cin >> s;
        add(root, s, 0);
    }

    cout << get(root);
    return 0;
}
