#include <bits/stdc++.h>

#define int long long
#define pii pair<int, int>
#define pb push_back
#define ff first
#define ss second
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
//#define forn(i, x) for (int i = 0; i < (int)x; i++)
#define rforn(i, n) for (int i = (int)x - 1; i >= 0; i--)
//#define print(x) forn (i, (x).size()) cout << x[i] << ' '; cout << '\n';

#define Pair pair<node*, node*>

using namespace std;

const int INF = 1e9 + 7;

struct node
{
    node *l, *r;
    int y, v, _min, sz;
    bool rev;

    node()
    {
        l = nullptr;
        r = nullptr;
        y = rand();
        _min = INF;
        v = -1;
        sz = 1;
        rev = false;
    }
};

int get_min(node* p)
{
    return (p ? p-> _min : INF);
}

int get_size(node* p)
{
    return (p ? p-> sz : 0);
}

void update(node* p)
{
    p-> _min = min(p-> v, min(get_min(p-> l), get_min(p-> r)));
    p-> sz = get_size(p-> l) + get_size(p-> r) + 1;
}

void push(node* p)
{
    if (p-> rev)
    {
        if (p-> l)
            p-> l-> rev ^= true;
        if (p-> r)
            p-> r-> rev ^= true;
        swap(p-> l, p-> r);
        p-> rev = false;
    }
}

node* merge(node* p1, node* p2)
{
    if (!p1)
        return p2;
    if (!p2)
        return p1;
    push(p1);
    push(p2);
    if (p1-> y < p2-> y)
    {
        p2-> l = merge(p1, p2-> l);
        update(p2);
        return p2;
    }
    else
    {
        p1-> r = merge(p1-> r, p2);
        update(p1);
        return p1;
    }
}

Pair split(node* p, int k)
{
    if (!p)
        return Pair(nullptr, nullptr);
    push(p);
    int sz = get_size(p-> l);
    if (sz + 1 <= k)
    {
        Pair t = split(p-> r, k - sz - 1);
        p-> r = t.ff;
        update(p);
        return Pair(p, t.ss);
    }
    else
    {
        Pair t = split(p-> l, k);
        p-> l = t.ss;
        update(p);
        return Pair(t.ff, p);
    }
}

void print(node* p)
{
    if (!p)
        return;
    print(p-> l);
    cout << p-> v << ' ';
    print(p-> r);
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    node* root = nullptr;

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        node* t = new node();
        t-> v = x;
        t-> _min = x;
        root = merge(root, t);
    }

    for (int i = 0; i < m; i++)
    {
        int type, l, r;
        cin >> type >> l >> r;
        if (type == 1)
        {

            Pair t = split(root, r);
            Pair t1 = split(t.ff, l - 1);
            t1.ss-> rev ^= true;
            root = merge(t1.ff, t1.ss);
            root = merge(root, t.ss);
        }
        else
        {
            Pair t = split(root, r);
            Pair t1 = split(t.ff, l - 1);
            cout << t1.ss-> _min << '\n';
            root = merge(t1.ff, t1.ss);
            root = merge(root, t.ss);
        }
    }

    return 0;
}
