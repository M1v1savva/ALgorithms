struct node
{
    map<int, int> son;
    map<int, int> go;
    int parent, suff_link, up;
    int p_val;
    bool leaf;
    vector<int> leaves;

    node()
    {
        parent = 0;
        suff_link = 0;
        up = 0;
        p_val = 0;
        leaf = false;
    }

    node& operator = (const node& r)
    {
        son = r.son;
        go = r.go;
        parent = r.parent;
        suff_link = r.suff_link;
        up = 0;
        p_val = r.p_val;
        leaf = r.leaf;
        leaves = r.leaves;
    }
};

int counter_of_allocated_nodes;
vector<node> t;

int get_node()
{
    return counter_of_allocated_nodes++;
}

void add(string &s, int numb)
{
    int current = root;
    forn (i, s.size())
    {
        int id = s[i] - 'a';
        if (t[current].son[id] == 0)
        {
            int next = get_node();
            t[next].parent = current;
            t[next].p_val = id;
            t[current].son[id] = next;
            current = next;
        }
        else
            current = t[current].son[id];
    }
    t[current].leaf = true;
    t[current].leaves.pb(numb);
}

int get_suff_link(int v);

int get_link(int v, int c)
{
    if (t[v].go[c] == 0)
    {
        if (t[v].son[c] != 0)
            t[v].go[c] = t[v].son[c];
        else if (v == root)
            t[v].go[c] = root;
        else
            t[v].go[c] = get_link(get_suff_link(v), c);
    }
    return t[v].go[c];
}

int get_suff_link(int v)
{
    if (t[v].suff_link == 0)
    {
        if (v == root || t[v].parent == root)
            t[v].suff_link = root;
        else
            t[v].suff_link = get_link(get_suff_link(t[v].parent), t[v].p_val);
    }
    return t[v].suff_link;
}


int get_up(int v)
{
    if (t[v].up == 0)
    {
        if (t[get_suff_link(v)].leaf)
            t[v].up = get_suff_link(v);
        else if (get_suff_link(v) == root)
            t[v].up = root;
        else
            t[v].up = get_up(get_suff_link(v));
    }
    return t[v].up;
}
