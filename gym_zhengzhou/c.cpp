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
    int x = 0;
};
Info operator +(Info a, Info b) {
    return Info{max(a.x, b.x)};
}
SegTree<Info, Info> seg;

void solve() {
    int n;
    cin >> n;
    vector<int> mn(n + 5, 1e9), mx(n + 5, -1e9);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        chkmin(mn[x], i);
        chkmax(mx[x], i);
    }
    vector<array<int, 3>> segs;
    for (int i = 1; i <= n; i++) {
        if (mn[i] == (int)1e9) {
            continue;
        }
        int l, r;
        l = mn[i];
        r = mx[i];
        segs.pb({l, r, i});
    }
    sort(all(segs));
    int rm = -1;
    int idx = 0;
    vector<vector<int>> hav;
    vector<int> cur;
    for (auto &seg : segs) {
        if (rm == -1) {
            rm = seg[1];
            cur.pb(seg[2]);
        } else {
            if (seg[0] <= rm) {
                rm = max(rm, seg[1]);
                cur.pb(seg[2]);
            } else {
                hav.pb(cur);
                cur.clear();
                rm = seg[1];
                cur.pb(seg[2]);
            }
        }
    }
    hav.pb(cur);
    seg.init(n);
    int tot = 0;
    for (auto cur : hav) {
        tot += cur.size();
        vector<pii> modify;
        for (int v : cur) {
            int nw = seg.ask(1, v).x + 1;
            modify.eb(v, nw);
        }
        for (auto [v, nw] : modify) {
            seg.upd(v, {nw});
        }
    }
    cout << tot - seg.ask(1, n).x << '\n';
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
