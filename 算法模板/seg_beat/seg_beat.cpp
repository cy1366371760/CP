#include<bits/stdc++.h>
#define pb push_back
#define ll long long
#define trav(v,x) for(auto v:x)
using namespace std;
const int N = 1e6 + 10;

#define EF if(ch==EOF) return x;
// #define lc k<<1
// #define rc k<<1|1
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;EF;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

struct gg{
    ll fi, sc;
	int num, l, r;// first mx  second mx  number of first mx
    ll sum = 0;
}seg[N << 2];

int n, a[N]; 

void push_up(int k)
{
	int ls = k << 1;
	int rs = k << 1 | 1;
    seg[k].num = 0;
    seg[k].sum = seg[ls].sum + seg[rs].sum;
    seg[k].fi = max(seg[ls].fi, seg[rs].fi);
    seg[k].sc = max(seg[ls].sc, seg[rs].sc);
    if(seg[ls].fi != seg[k].fi)seg[k].sc = max(seg[k].sc, seg[ls].fi);
    if(seg[rs].fi != seg[k].fi)seg[k].sc = max(seg[k].sc, seg[rs].fi);
    if(seg[k].fi == seg[ls].fi)seg[k].num += seg[ls].num;
	if(seg[k].fi == seg[rs].fi)seg[k].num += seg[rs].num;
}

void build(int l = 1, int r = n, int k = 1)
{
	seg[k].l = l;
	seg[k].r = r;
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
	if(seg[k << 1].fi > seg[k].fi)
	{
 	    seg[k << 1].sum += 1LL * (seg[k].fi - seg[k << 1].fi) * seg[k << 1].num;
   		seg[k << 1].fi = seg[k].fi;
	}
    if(seg[k << 1 | 1].fi > seg[k].fi)
    {
	    seg[k << 1 | 1].sum += 1LL * (seg[k].fi - seg[k << 1 | 1].fi) * seg[k << 1 | 1].num;
   		seg[k << 1 | 1].fi = seg[k].fi;
	}
}

void upd(int L, int R, int val, int k = 1)
{
    if(seg[k].fi <= val)return;
    if(seg[k].fi > val && seg[k].sc <= val)
    {
		seg[k].sum += 1LL * (val - seg[k].fi) * seg[k].num;
		seg[k].fi = val;
        return;
    }
    if(seg[k].l < seg[k].r)push_down(k);
	int mid = (seg[k].l + seg[k].r) >> 1;
    if(L <= mid)upd(L, R, val, k << 1);
    if(R > mid)upd(L, R, val, k << 1 | 1);
    push_up(k);
}

ll ask_mx(int L, int R, int k = 1)
{
    if(seg[k].l > R || seg[k].r < L)return -1;
    if(L <= seg[k].l && seg[k].r <= R)return seg[k].fi;
    if(seg[k].l != seg[k].r)push_down(k);
    return max(ask_mx(L, R, k << 1), ask_mx(L, R, k << 1 | 1));
}

ll ask_sum(int L, int R, int k = 1)
{
    if(seg[k].l > R || seg[k].r < L)return 0;
    if(L <= seg[k].l && seg[k].r <= R)return seg[k].sum;
    if(seg[k].l != seg[k].r)push_down(k);
    return ask_sum(L, R, k << 1) + ask_sum(L, R, k << 1 | 1);
}

template<class T>
void output(T x)
{
	if(x >= 10)output(x / 10);
	putchar('0' + x % 10);
}

signed main()
{
    int tt;
//	freopen("1.in", "r", stdin);
//	freopen("1.out", "w" ,stdout);
    tt = read();
    while(tt--)
    {
        int ttt;
        n = read(), ttt = read();
        for(int i = 1; i <= n; i++)
            a[i] = read();
        build();
        while(ttt--)
        {
            int opt, x, y, val;
            opt = read(), x = read(), y = read();
            if(opt == 0)val = read(), upd(x, y, val);
            if(opt == 1)output(ask_mx(x, y)), putchar('\n');
            if(opt == 2)output(ask_sum(x, y)), putchar('\n');
        }
    }
    return 0;
}
