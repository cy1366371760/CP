mt19937 rng(time(0));  
struct Node {  
    int fa;  
    int ch[2], w, rnd, laz, sz;  
    bool rev;  
} node[N];  
  
#define ls node[nw].ch[0]  
#define rs node[nw].ch[1]  
  
int tot;  
void push_up(int nw)  
{  
    node[nw].sz = node[ls].sz + node[rs].sz + 1;  
    if(ls)node[ls].fa = nw;  
    if(rs)node[rs].fa = nw;  
}  
int new_node(int w)  
{  
    int nw = ++tot;  
    node[nw].rnd = rng();  
    node[nw].laz = node[nw].rev = 0;  
    ls = rs = 0;  
    node[nw].sz = 1;  
    node[nw].fa = 0;  
    node[nw].w = w;  
    return nw;  
}  
void R(int nw)  
{  
    if (!nw) {  
        return;  
    }  
    swap(ls, rs);  
    node[nw].rev ^= 1;  
}  
void push_down(int nw)  
{  
    if (node[nw].rev) {  
        R(ls), R(rs);  
        node[nw].rev = 0;  
    }  
}  
int mg(int x, int y)  
{  
    if (!x || !y) {  
        return x + y;  
    }  
    push_down(x), push_down(y);  
    if (node[x].rnd <= node[y].rnd) {  
        node[x].ch[1] = mg(node[x].ch[1], y);  
        push_up(x);  
        return x;  
    } else {  
        node[y].ch[0] = mg(x, node[y].ch[0]);  
        push_up(y);  
        return y;  
    }  
}  
void split1(int nw, int k, int &x, int &y)  
{  
    if (!nw) {  
        x = y = 0;  
    } else {  
        push_down(nw);  
        node[nw].fa = 0;  
        if (node[ls].sz >= k) {  
            y = nw, split1(ls, k, x, ls);  
        } else {  
            x = nw, split1(rs, k - node[ls].sz - 1, rs, y);  
        }  
        push_up(nw);  
    }  
}  
void split2(int nw, int k, int &x, int &y)  
{  
    if (!nw) {  
        x = y = 0;  
    } else {  
        push_down(nw);  
        node[nw].fa = 0;  
        if (node[nw].w <= k) {  
            x = nw, split2(rs, k, rs, y);  
        } else {  
            y = nw, split2(ls, k, x, ls);  
        }  
        push_up(nw);  
    }  
}  
void ins(int &nw, int val)  
{  
    static int x, y;  
    split2(nw, val, x, y);  
    nw = mg(mg(x, new_node(val)), y);  
    return;  
}  
vector<int> get_all(int nw)  
{  
    if (nw == 0) {  
        return vector<int> {};  
    }  
    push_down(nw);  
    vector<int> l, r;  
    l = get_all(ls);  
    r = get_all(rs);  
    l.pb(node[nw].w);  
    for (auto v : r) {  
        l.pb(v);  
    }  
    return l;  
}  
  
int find_rt(int nw)  
{  
    while(node[nw].fa) {  
        nw = node[nw].fa;  
    }  
    return nw;  
}  
  
bool is_rs(int nw)  
{  
    if (!nw || nw == node[node[nw].fa].ch[0]) {  
        return 0;  
    }  
    return 1;  
}  
  
int get_rnk(int nw)  
{  
    int res = node[ls].sz + 1;  
    while(node[nw].fa) {  
        if (is_rs(nw)) {  
            nw = node[nw].fa;  
            res += node[ls].sz + 1;  
        } else {  
            nw = node[nw].fa;  
        }  
    }  
    return res;  
}  
