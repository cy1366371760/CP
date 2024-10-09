#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define sc second
#define pb push_back
#define ll long long
#define trav(v,x) for(auto v:x)
using namespace std;
const int N = 1e6 + 100;

void Mn(int &x, int y)
{x = min(x, y);}

struct gg{
    int fi, sc, num;// first mx  second mx  number of first mx
    ll sum = 0;
}seg[N << 2];

int n, a[N]; 

void P(gg &x, gg &y)
{
    x.sum += y.sum;
    if(y.fi == x.fi)
    {
    	x.num += y.num;
    	x.sc = max(x.sc, y.sc);
    	return;
	}
    if(x.sc < y.fi)x.sc = y.fi;
    if(x.fi < x.sc)swap(x.fi, x.sc), x.num = 0;
    if(x.sc < y.sc)x.sc = y.sc;
    if(x.fi == y.fi)x.num += y.num;
    return;
}

void push_up(int k)
{
    seg[k].fi = -1;
    seg[k].sc = -1;
    seg[k].num = 0;
    seg[k].sum = 0;
    P(seg[k], seg[k << 1]);
    P(seg[k], seg[k << 1 | 1]);
}

void build(int l = 1, int r = n, int k = 1)
{
    if(l == r)
    {
        seg[k].fi = a[l];
        seg[k].sc = -1;
        seg[k].num = 1;
        seg[k].sum = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, k << 1);
    build(mid + 1, r, k << 1 | 1);
    push_up(k);
}

void push_down(int k)
{
    seg[k << 1].sum -= 1LL * seg[k << 1].fi * seg[k << 1].num;
    Mn(seg[k << 1].fi, seg[k].fi);
    seg[k << 1].sum += 1LL * seg[k << 1].fi * seg[k << 1].num;
    
    seg[k << 1 | 1].sum -= 1LL * seg[k << 1 | 1].fi * seg[k << 1 | 1].num;
    Mn(seg[k << 1 | 1].fi, seg[k].fi);
    seg[k << 1 | 1].sum += 1LL * seg[k << 1 | 1].fi * seg[k << 1 | 1].num;
}

void upd(int L, int R, int val, int l = 1, int r = n, int k = 1)
{
    if(l > R || r < L)return;
    if(l < r)push_down(k);
    if(L <= l && r <= R)
    {
        if(seg[k].fi <= val)return;
        if(seg[k].fi > val && seg[k].sc <= val)
        {
            seg[k].sum -= 1LL * seg[k].fi * seg[k].num;
            seg[k].fi = val;
            seg[k].sum += 1LL * seg[k].fi * seg[k].num;
            return;
        }
    }
    int mid = (l + r) >> 1;
    upd(L, R, val, l, mid, k << 1);
    upd(L, R, val, mid + 1, r, k << 1 | 1);
    push_up(k);
}

int ask_mx(int L, int R, int l = 1, int r = n, int k = 1)
{
    if(l > R || r < L)return -1;
    if(l < r)push_down(k);
    if(L <= l && r <= R)
    {
        return seg[k].fi;
    }
    int mid = (l + r) >> 1;
    return max(ask_mx(L, R, l, mid, k << 1), ask_mx(L, R, mid + 1, r, k << 1 | 1));
}

ll ask_sum(int L, int R, int l = 1, int r = n, int k = 1)
{
    if(l > R || r < L)return 0;
    if(l < r)push_down(k);
    if(L <= l && r <= R)
    {
        return seg[k].sum;
    }
    int mid = (l + r) >> 1;
    return ask_sum(L, R, l, mid, k << 1) + ask_sum(L, R, mid + 1, r, k << 1 | 1);
}

signed main()
{
//		freopen("1.in", "r", stdin);
//	freopen("3.out", "w" ,stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt;
    cin >> tt;
    while(tt--)
    {
        int ttt;
        cin >> n >> ttt;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        build();
        while(ttt--)
        {
            int opt, x, y, val;
            cin >> opt >> x >> y;
            if(opt == 0)cin >> val, upd(x, y, val);
            if(opt == 1)cout << ask_mx(x, y) << '\n';
            if(opt == 2)cout << ask_sum(x, y) << '\n';
        }
    }
    return 0;
}
