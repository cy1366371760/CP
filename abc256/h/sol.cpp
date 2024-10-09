#include<bits/stdc++.h>

#define ll long long
#define int long long
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define eb emplace_back
#define fi first
#define sc second

#define pii pair<int, int>
#define pll pair<ll, ll>
template<typename T> bool chkmin(T &a, T b){return (b < a) ? a = b, 1 : 0;}
template<typename T> bool chkmax(T &a, T b){return (b > a) ? a = b, 1 : 0;}
using namespace std;
using ld = long double;
const int N = 1e6 + 100;
const ll inf = 1e18;
const ll mod = 998244353;

template<class Info, class Lazy>
struct SegTree {
	#define ls k << 1
	#define rs k << 1 | 1
	#define mid ((l + r) >> 1)
	int n;
	vector<Info> seg;
	vector<bool> tag;
	vector<Lazy> laz;
	
	void push_up(int k) {
		seg[k] = seg[ls] + seg[rs];
	}
	void change(int k, Lazy val) {
		seg[k] = seg[k] + val;
		if (tag[k]) {	
			laz[k] = laz[k] + val;
		} else {
			laz[k] = val;
		}
		tag[k] = 1;
	}
	void push_down(int k) {
		if (tag[k]) {
			change(ls, laz[k]);
			change(rs, laz[k]);
			tag[k] = 0;
			laz[k] = {};
		}
	}
	void init(int _n) {
		n = _n;
		seg.clear(), seg.resize(n * 4 + 100);
		tag.clear(), tag.resize(n * 4 + 100);
		laz.clear(), laz.resize(n * 4 + 100);
		return;
	}
	void init(vector<Info> bg) {
		init(bg.size() - 1);
		function<void(int, int, int)> build = [&](int l, int r, int k) {
			if (l == r) return (void)(seg[k] = bg[l]);
			build(l, mid, ls), build(mid + 1, r, rs);
			push_up(k);	
		};
		build(1, n, 1);
	}
	Info ask(int L, int R, int l, int r, int k) {
		if (l > R || r < L) return Info();
		if (L <= l && r <= R) {
			return seg[k];
		}
		push_down(k);
		return ask(L, R, l, mid, ls) + ask(L, R, mid + 1, r, rs);
	}
	Info ask(int L, int R) {
		return ask(L, R, 1, n, 1);
	}
	void upd(int to, Info val, int l, int r, int k) {
		if (l == r) return (void)(seg[k] = val);
		push_down(k);
		if (to <= mid) upd(to, val, l, mid, ls);
		else upd(to, val, mid + 1, r, rs);
		push_up(k);
	}
	void upd(int to, Info val) {
		upd(to, val, 1, n, 1);
	}
	void add(int L, int R, Lazy val, int l, int r, int k) {
		if (l > R || r < L) return;
		if (L <= l && r <= R) {
			change(k, val);
			return;
		}
		push_down(k);
		add(L, R, val, l, mid, ls);
		add(L, R, val, mid + 1, r, rs);
		push_up(k);
	}
	void add(int L, int R, Lazy val) {
		// cerr << "fuck" << L << ' ' << R << ' ' << val.v << ' ' << n << '\n';
		add(L, R, val, 1, n, 1);
	}
	int rnk; // 下面两个查询，如果查区间第k大时用，下面两个询问均返回位置 
	template<class F>
	int findFirst(int L, int R, int l, int r, int k, F pred) {
        if (l > R || r < L || !pred(seg[k])) {
        	if (L <= l && r <= R) rnk -= seg[k].cnt;
            return -1;
        }
        if (l == r) {
            return l;
        }
        push_down(k);
        int res = findFirst(L, R, l, mid, ls, pred);
        if (res == -1) {
            res = findFirst(L, R, mid + 1, r, rs, pred);
        }
        return res;
    }
    template<class F>
    int findFirst(int l, int r, F pred, int need) {
    	rnk = need;
        return findFirst(l, r, 1, n, 1, pred);
    }
    template<class F>
    int findLast(int L, int R, int l, int r, int k, F pred) {
        if (l > R || r < L || !pred(seg[k])) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        push_down(k);
        int res = findLast(L, R, mid + 1, r, rs, pred);
        if (res == -1) {
            res = findLast(L, R, l, mid, ls, pred);
        }
        return res;
    }
    template<class F>
    int findLast(int l, int r, F pred) {
        return findLast(l, r, 1, n, 1, pred);
    }
	#undef ls 
	#undef rs
	#undef mid
};
/*
(1) implement struct Info
(2) implement struct Lazy
(3) implement Info operator +(Info a, Info b)
(4) implement Info operator +(Info a, Lazy b)
(5) implement Lazy operator +(Lazy a, Lazy b)

*when not need Lazy, use SegTree<Info, Info>, so can only implement (1) (3)
*Lazy can be long long or some default type, so can only implement (1) (3) (4)

.init(vector bg/size_bg) should give vector or size
vector first element should start from 1 (index 0 not use)
*/

struct Info {
    ll v = 0;
	int l = 0, r = 0;
};

struct Lazy {
    ll v = 0;
};

Info operator +(Info a, Info b) {
    return {a.v + b.v, min(a.l, b.l), max(a.r, b.r)};
}

Info operator +(Info a, Lazy b) {
    return {b.v * (a.r - a.l + 1), a.l, a.r};
}

Lazy operator + (Lazy a, Lazy b) {
    return b;
}

SegTree<Info, Lazy> seg;

void solve() {
    int n, qq;
    cin >> n >> qq;
    vector<Info> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i].v;
		a[i].l = a[i].r = i;
    }
    seg.init(a);
	set<array<ll, 3>> st;
	for (int i = 1; i <= n; i++) {
		int j = i;
		while (j <= n && a[j].v == a[i].v) ++j;
		--j;
		st.insert({i, j, a[i].v});
		i = j;
	}
	auto merge = [&](auto ii) -> void {
		if (ii == st.end())return;
		auto [l, r, val] = (*ii);
		if (ii != st.begin()) {
			auto jj = prev(ii);
			if ((*jj)[2] == val) {
				chkmin(l, (*jj)[0]);
				st.erase(jj);
				st.erase(ii);
				st.insert({l, r, val});
			}
		}
	};
	while (qq--) {
		ll type, l, r, x;
		cin >> type >> l >> r;
		if (type < 3) cin >> x;
		if (type == 3) {
			cout << seg.ask(l, r).v << '\n';
		} else if (type == 1) {
			auto ii = st.upper_bound({l, n + 1, inf});
			ii = prev(ii);
			while (1) {
				auto jj = next(ii);
				auto [nl, nr, val] = (*ii);
				if (nl > r) break;
				st.erase(ii);
				if (nl < l) {
					st.insert({nl, l - 1, val});
				}
				merge(st.insert({max(nl, l), min(nr, r), val / x}).fi);
				seg.add(max(nl, l), min(nr, r), {val / x});
				if (nr > r) {
					merge(st.insert({r + 1, nr, val}).fi);
				}
				if (jj == st.end()) break;
				ii = jj;
			}
		} else {
			auto ii = st.upper_bound({l, n + 1, inf});
			ii = prev(ii);
			seg.add(l, r, {x});
			while (1) {
				auto jj = next(ii);
				auto [nl, nr, val] = (*ii);
				if (nl > r) break;
				st.erase(ii);
				if (nl < l) {
					st.insert({nl, l - 1, val});
				}
				if (nr > r) {
					st.insert({r + 1, nr, val});
				}
				if (jj == st.end()) break;
				ii = jj;
			}
			ii = st.insert({l, r, x}).first;
			auto jj = next(ii);
			merge(ii), merge(jj);
		}
		// cerr << "!!!!!" << '\n';
		// for (auto [l, r, val] : st) cerr << l << ' ' << r << ' ' << val << '\n';
	}
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // int tt = 1;
    // cin >> tt;
    // while(tt--)
        solve();
    return 0;
}