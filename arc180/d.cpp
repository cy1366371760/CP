#include<bits/stdc++.h>

#define ll long long
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

struct Info_max {
    int mx = 0;
};
Info_max operator + (const Info_max &a, const Info_max &b) {
    return {max(a.mx, b.mx)};
}

SegTree<Info_max, Info_max> seg_max;

struct Info {
    int v = 1e9;
    int pre = 1e9;
    int s = 1e9; // s = v + pre
};

Info operator + (const Info &a, const Info &b) {
    Info res;
    res.v = min(a.v, b.v);
    res.pre = min(a.pre, b.pre);
    res.s = min(a.s, b.s);
    return res;
}

struct Lazy {
    int pre = 0;
};
Lazy operator + (const Lazy &a, const Lazy &b) {
    return {max(a.pre, b.pre)};
}
Info operator + (const Info &a, const Lazy &b) {
    Info res;
    res.v = a.v;
    assert(a.pre <= b.pre);
    res.pre = b.pre;
    res.s = res.v + res.pre;
    return res;
}

SegTree<Info, Lazy> seg;


void solve() {
    int n, qq;
    cin >> n >> qq;
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<Info_max> bg(n + 1);
    for (int i = 1; i <= n; i++) {
        bg[i].mx = a[i];
    }
    seg_max.init(bg);
    vector<int> ans(qq + 1, 0);
    vector<vector<pii>> qry1(n + 5), qry2(n + 5);
    for (int i = 1; i <= qq; i++) {
        int l, r;
        cin >> l >> r;
        ans[i] = seg_max.ask(l + 2, r).mx + a[l] + a[l + 1];
        chkmin(ans[i], seg_max.ask(l + 1, r - 1).mx + a[l] + a[r]);
        chkmin(ans[i], seg_max.ask(l, r - 2).mx + a[r] + a[r - 1]);
        qry1[l].pb({r, i});
        qry2[n + 1 - r].pb({n + 1 - l, i});
    }
    for (int opt = 1; opt <= 2; opt++) {
        
        seg.init(n);
        for (int l = n; l >= 1; l--) {
            int nw = a[l];
            seg.upd(l, {nw, 0, nw});
            int ps = seg.findLast(l + 1, n, [&](Info x) {
                return x.pre <= nw;
            });
            if (ps != -1) {
                // if (opt == 2) cerr << "miao: " << l << ' ' << ps << ' ' << nw << '\n';
                seg.add(l + 1, ps, {nw});
            }
            for (auto [r, id] : qry1[l]) {
                int res = seg.ask(l + 1, r).s;
                if (opt == 1) res += seg_max.ask(l, r).mx;
                else res += seg_max.ask(n + 1 - r, n + 1 - l).mx;
                chkmin(ans[id], res);
                // if (id == 1) {
                //     cerr << seg.ask(l, r).s << ' ' << seg_max.ask(l, r).mx << '\n';
                //     cerr << l << ' ' << r << ' ' << res << '\n';
                // }
            }
        }
        reverse(a.begin() + 1, a.end());
        // cerr <<"GGG" << '\n';
        // for (int i = 1; i <= n; i++) {
        //     cerr << a[i] << ' ';
        // }
        swap(qry1, qry2);
    }
    for (int i = 1; i <= qq; i++) {
        cout << ans[i] << '\n';
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
