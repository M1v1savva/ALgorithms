struct point
{
    char c;
    int r, b;

    point() {}
    point(char _c, int _r, int _b) : c(_c), r(_r), b(_b) {}
    ~point() {}
};

int n, ans;
vector<point> data;
vector<int> res, cur;

int f()
{
    int a = 0, b = 0, counter = 0, rv = 0, bv = 0;
    for(int i = 0; i < n; i++)
    {
        int id = cur[i];
        int rc = max(data[id].r - a, 0ll), bc = max(data[id].b - b, 0ll);
        int del = max(max(rc - rv, 0ll), max(bc - bv, 0ll));
        rv += del;
        bv += del;
        rv -= rc;
        bv -= bc;
        counter += del + 1;
        if(data[id].c == 'R')
            a++;
        else
            b++;
    }
    return counter;
}

double rnd()
{
    return double(rand())/double(RAND_MAX);
}

signed main()
{
    cin >> n;
    res.resize(n);
    cur.resize(n);

    for(int i = 0; i < n; i++)
    {
        char c;
        int r, b;
        cin >> c >> r >> b;
        data.push_back(point(c, r, b));
        res[i] = i;
    }

    random_shuffle(res.begin(), res.end());
    cur = res;

    ans = f();
    int min_ans = ans;
    double t = 1000;
    clock_t start = clock();
    while(clock() - start < 0.992*2*CLOCKS_PER_SEC)
    {
        t *= 0.99999;
        cur = res;
        swap(cur[rand() % n], cur[rand() % n]);
        int val = f();

        if(val < ans || rnd() < exp(double(ans - val)/t))
        {
            ans = val;
            min_ans = min(min_ans, ans);
            res = cur;
        }
    }

    cout << min_ans;
    return 0;
}
