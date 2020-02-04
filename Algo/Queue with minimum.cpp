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

struct mQueue
{
    queue<int> q;
    deque<int> v;
    mQueue() {}

    void push(int x)
    {
        q.push(x);
        while (v.size() && x < v.back())
            v.pop_back();
        v.pb(x);
    }
    void pop()
    {
        int x = q.front();
        q.pop();
        if (v[0] == x)
            v.pop_front();
    }
    int get()
    {
        return v.front();
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

    mQueue q;

    forn (i, k)
        q.push(a[i]);

    cout << q.get() << '\n';
    for (int i = k; i < n; i++)
    {
        q.pop();
        q.push(a[i]);
        cout << q.get() << '\n';
    }

    return 0;
}
