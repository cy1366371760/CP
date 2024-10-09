#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define sc second
#define pb push_back
#define ll long long
#define trav(v,x) for(auto v:x)
using namespace std;
const int N = 2e5 + 100;
const int inf = 2e9;

int n;
int a[N];

struct node{
	int fi, sc, num;// first and second min
	int sum, val[31];
}seg[N << 2];

void push_up(int x)
{
	node &nw = seg[x], &l = seg[x << 1], &r = seg[x << 1 | 1];
	nw.sum = l.sum ^ r.sum;
	for(int i = 0; i <= 30; i++)
		nw.val[i] = l.val[i] + r.val[i];
	nw.fi = min(l.fi, r.fi);
	nw.sc = min(l.sc, r.sc);
	if(nw.fi != l.fi)nw.sc = min(nw.sc, l.fi);
	if(nw.fi != r.fi)nw.sc = min(nw.sc, r.fi);
	nw.num = 0;
	if(nw.fi == l.fi)nw.num += l.num;
	if(nw.fi == r.fi)nw.num += r.num;
	return;
}

void cg(node &x, int w)
{
	int tmp = x.fi;
	for(int i = 0; i <= 30; i++)
	{
		if(tmp & 1)x.val[i] -= x.num;
		tmp >>= 1;
	}
	if(x.num & 1)
		x.sum ^= x.fi;
	x.fi = tmp = w;
	for(int i = 0; i <= 30; i++)
	{
		if(tmp & 1)x.val[i] += x.num;
		tmp >>= 1;
	}
	if(x.num & 1)
		x.sum ^= x.fi;
}

void push_down(int x)
{
	node &nw = seg[x];
	int tmp;
	for(int son = 0; son <= 1; son++)
	{
		node &y = seg[x << 1 | son];
		if(nw.fi > y.fi)
		{
			cg(y, nw.fi);
		}
	}
}

void build(int l = 1, int r = n, int k = 1)
{
	if(l == r)
	{
		seg[k].fi = a[l];
		seg[k].sc = inf;
		seg[k].num = 1;
		seg[k].sum = a[l];
		for(int i = 0, tmp = a[l]; i <= 30; i++)
		{
			seg[k].val[i] = tmp & 1;
			tmp >>= 1;
		}
		return;
	}
	int mid = l + r >> 1;
	build(l, mid, k << 1);
	build(mid + 1, r, k << 1 | 1);
	push_up(k);
}

void upd(int L, int R, int w, int l = 1, int r = n, int k = 1)
{
	if(l > R || r < L)return;
	if(l < r)push_down(k);
	if(L <= l && r <= R)
	{
		if(w <= seg[k].fi)return;
		if(seg[k].fi < w && w <= seg[k].sc)
		{
			cg(seg[k], w);
			return;
		}
	}
	int mid = l + r >> 1;
	upd(L, R, w, l, mid, k << 1);
	upd(L, R, w, mid + 1, r, k << 1 | 1);
	push_up(k);
	return;
}

int qry_sum(int L, int R, int l = 1, int r = n, int k = 1)
{
	if(l > R || r < L)return 0;
	if(l < r)push_down(k);
	if(L <= l && r <= R)
	{
		return seg[k].sum;
	}
	int mid = l + r >> 1;
	return qry_sum(L, R, l, mid, k << 1) ^ qry_sum(L, R, mid + 1, r, k << 1 | 1);
}

int qry_val(int L, int R, int ps, int l = 1, int r = n, int k = 1)
{
	if(l > R || r < L)return 0;
	if(l < r)push_down(k);
	if(L <= l && r <= R)
	{
		return seg[k].val[ps];
	}
	int mid = l + r >> 1;
	return qry_val(L, R, ps, l, mid, k << 1) + qry_val(L, R, ps, mid + 1, r, k << 1 | 1);
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int tt;
	cin >> n >> tt;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	build();
	while(tt--)
	{
		int op, l, r, x;
		cin >> op >> l >> r >> x;
		if(op == 1)
		{
			upd(l, r, x);
		}
		else
		{
			int tmp = qry_sum(l, r) ^ x, y;
			if(tmp == 0)
			{
				cout << 0 << '\n';
				continue;
			}
			for(int i = 0; i <= 30; i++)
			{
				if(tmp & 1)y = i;
				tmp >>= 1;
			}
			int res = qry_val(l, r, y);
			if(x & (1 << y))++res;
			cout << res << '\n';
		}
	}
	return 0;
}


