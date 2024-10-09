const int Size = 1e6 + 100;
int fa[Size], cnt, is[Size];
int find(int x){
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
struct leftist{
	struct point{
		int l,r,d,v,t,to;
	}a[Size]={{0, 0, -1, 0, 0, 0}};
	int r[Size];
	void merge(int &x, int &y) {
		if (!x || !y) {
			x = x + y; 
			return;
		}
		if (a[x].v > a[y].v) {
			swap(x, y);
		}
		a[y].t -= a[x].t, a[y].v -= a[x].t;
		merge(a[x].r, y);
		if(a[a[x].l].d < a[a[x].r].d)
			swap(a[x].l, a[x].r);
		a[x].d = a[a[x].r].d + 1;
	}
	void spread(int &p) {
		a[a[p].l].t += a[p].t, a[a[p].r].t += a[p].t;
		a[a[p].l].v += a[p].t, a[a[p].r].v += a[p].t;
		a[p].t = 0;
	}
	void pop(int &x) {
		spread(x), merge(a[x].l, a[x].r), x = a[x].l;
	}
	point*top(int &x) {
		while (r[x] && find(a[r[x]].to) == x) {
			pop(r[x]);
		}
		if (!r[x]) {
			cout << -1 << '\n';
			exit(0);
		}
		a[r[x]].to = find(a[r[x]].to);
		return &a[r[x]];
	}
}L;
void Union(int u, int v){
	if ((u=find(u)) != (v=find(v)))
		L.merge(L.r[v], L.r[u]), fa[u] = v;
}
int pre[Size];

void sol()
{
	int n, m, r, ans = 0;
	leftist::point *temp;
	cin >> n >> m >> r;
	cnt = n, is[r] = r;
	for (int i = 1, u, v, w; i <= m; i++) {
		cin >> u >> v >> w;
		L.a[i] = {0, 0, 0, w, 0, u};
		L.merge(L.r[v], u = i);
	}
	for (int i = 1; i <= n << 1; i++) fa[i] = i;
	for (int i = 1, j = i; i <= n; j = ++i) {
		while (!is[j]) {
			while (!is[j]) {
				is[j] = i, j = (temp = L.top(j)) -> to;
				ans += temp -> v;
			}
			if (is[j] != i) break;
			while (~is[j]) {
				is[j] = -1, j = pre[j] = (temp = L.top(j)) -> to,
				temp -> t -= temp -> v, temp -> v = 0;
			}
			++cnt;
			while(is[j] != i) {
				is[j] = i, Union(j, cnt);
				j = pre[j];
			}
			j = cnt;
		}
	}
	cout << ans << '\n';
}