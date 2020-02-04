#include <bits/stdc++.h>

#define int long long
#define pii pair<int, int>
#define pb push_back
#define ff first
#define ss second
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define forn(i, x) for(int i = 0; i < x; i++)
#define rforn(i, x) for(int i = x - 1; i >= 0; i--)
#define printp(x) for(int i = 0; i < (x).size(); i++) cout << (x)[i] + 1 << " "; cout << endl;
#define print(x) for(int i = 0; i < (x).size(); i++) cout << (x)[i] << " "; cout << endl;

using namespace std;

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    forn (i, n)
        cin >> a[i];
    a.pb(0);
    n++;

    vector<vector<int> > srt(20);
    vector<int> p, c(n);

    forn (i, n)
        srt[a[i]].pb(i);

    int classes = 0;
    forn (i, 20)
    {
        for (int x : srt[i])
        {
            p.pb(x);
            c[x] = classes;
        }
        if (srt[i].size())
            classes++;
    }

    for (int len = 1; len < n; len *= 2)
    {
        forn (i, n)
        {
            p[i] -= len;
            p[i] += n;
            p[i] %= n;
        }

        srt.clear();
        srt.resize(n);
        forn (i, n)
            srt[c[p[i]]].pb(p[i]);

        p.clear();
        forn (i, n)
            for (int x : srt[i])
                p.pb(x);

        vector<int> cn(n);
        classes = 0;
        cn[p[0]] = classes;

        for (int i = 1; i < n; i++)
        {
            int mid1 = (p[i - 1] + len) % n, mid2 = (p[i] + len) % n;

            if (c[p[i - 1]] != c[p[i]] || c[mid1] != c[mid2])
                classes++;
            cn[p[i]] = classes;
        }
        c = cn;
    }

    vector<int> id(n);
    forn (i, n)
        id[p[i]] = i;

    vector<int> lcp(n);
    int k = 0;
    forn (i, n)
    {
        int pos = id[i];

        if (pos == 0)
        {
            k = 0;
            lcp[pos] = 0;
            continue;
        }

        if (k > 0)
            k--;

        int j = p[pos - 1];
        while (max(j + k, i + k) < n && a[i + k] == a[j + k])
            k++;
        lcp[pos - 1] = k;
    }
    lcp[n - 1] = 0;

    stack<vector<int> > st;

    int start = 0, max_numb = 1, max_len = n - 1;

    for (int i = 1; i < n; i++)
    {
        int current_number = 1;
        while (st.size() && st.top()[2] >= lcp[i])
        {
            vector<int> v = st.top();
            st.pop();

            current_number += v[1];

            if (current_number * v[2] > max_numb * max_len)
            {
                start = p[v[0]];
                max_len = v[2];
                max_numb = current_number;
            }
        }

        st.push({i, current_number, lcp[i]});
    }

    cout << max_numb * max_len << endl;
    cout << max_len << endl;
    for (int i = start; i < start + max_len; i++)
        cout << a[i] << ' ';
    return 0;
}
