typedef double T;

struct vec
{
    T x, y;

    vec() {}
    vec(T _x, T _y) : x(_x), y(_y) {}
    ~vec() {}

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
    vec operator * (const T &k)
    {
        return vec(x * k, y * k);
    }
    vec operator / (const T &k)
    {
        return vec(x / k, y / k);
    }
    T operator * (const vec &r)
    {
        return x * r.x + y * r.y;
    }
    T operator ^ (const vec &r)
    {
        return x * r.y - y * r.x;
    }
    double len()
    {
        return sqrt(x * x + y * y);
    }
    vec& normalize()
    {
        *this = (*this) / len();
        return *this;
    }
};

struct line
{
    T a, b, c;
    vec A, B;

    line() {}
    line(T _a, T _b, T _c) : a(_a), b(_b), c(_c)
    {
        if (b == 0)
        {
            A = vec(-c / a, 0);
            B = vec(-c / a, 1);
        }
        else
        {
            A = vec(0, (-c - a * 0) / b);
            B = vec(1, (-c - a * 1) / b);
        }
    }
    line(vec _A, vec _B)
    {
        A = _A;
        B = _B;
        T x1 = A.x, x2 = B.x, y1 = A.y, y2 = B.y;
        a = y2 - y1, b = x1 - x2, c = x2 * y1 - x1 * y2;
    }
};

vec intersect_lines(line l1, line l2)
{
    T a1 = l1.a, b1 = l1.b, c1 = l1.c;
    T a2 = l2.a, b2 = l2.b, c2 = l2.c;
    T x = (c2 * b1 - c1 * b2) / (b2 * a1 - a2 * b1);
    T y = (c2 * a1 - c1 * a2) / (a2 * b1 - a1 * b2);
    return vec(x, y);
}

bool bet(T v, T a, T b)
{
    return ((a <= v && v <= b) || (b <= v && v <= a));
}

bool on_ray(vec v, vec a, vec b)
{
    vec p1 = v - a, p2 = b - a;
    return (p1 ^ p2) == 0 && (p1 * p2) >= 0;
}



bool on_seg(vec v, vec a, vec b)
{
    return on_ray(v, a, b) && on_ray(v, b, a);
}

bool parallel(line a, line b)
{
    vec v1 = (a.A - a.B);
    vec v2 = (b.A - b.B);
    return (v1 ^ v2) == 0;
}

vec get_ort(vec v)
{
    return vec(-v.y, v.x);
}

line get_ort(vec v, line l)
{
    vec p = l.A - l.B;
    vec n = get_ort(p);
    return line(v, v + n);
}

T dist(vec v, line l)
{
    return fabs(v.x * l.a + v.y * l.b + l.c) / sqrt(l.a * l.a + l.b * l.b);
}

bool eq(line l1, line l2)
{
    if (!parallel(l1, l2))
        return false;
    T k = l1.a / l2.a;

    return (l1.b / l2.b == k && l1.c / l2.c == k);
}

istream& operator >> (istream &cin, vec &v)
{
    cin >> v.x >> v.y;
    return cin;
}

ostream& operator << (ostream &cout, vec v)
{
    cout << v.x << ' ' << v.y;
    return cout;
}
