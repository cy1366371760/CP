#include<bits/stdc++.h>

#define nl '\n'
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
/*
[1, 1, 1]

0, 1, sum

0:
1 1 1
0 1 0
0 0 1

1:
1 0 0
1 1 1
0 0 1

?:
1 1 1
1 1 1
0 0 1
*/
struct Info {
    ll a[3][3];
    Info () {
        memset(a, 0, sizeof a);
    };
    void to_unit() {
        memset(a, 0, sizeof a);
        for (int i = 0; i < 3; i++) {
            a[i][i] = 1;
        }
        return;
    }
};

Info operator +(Info a, Info b) {
    Info res;
    for (int k = 0; k < 3; k++) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                res.a[i][j] = (res.a[i][j] + a.a[i][k] * b.a[k][j]) % mod;
            }
        }
    }
    return res;
}


void solve() {
    int n, qq;
    cin >> n >> qq;
    string s;
    cin >> s;
    SegTree<Info, Info> seg;
    Info tmp[3];
    tmp[0].to_unit();
    tmp[0].a[0][1] = tmp[0].a[0][2] = 1;
    tmp[1].to_unit();
    tmp[1].a[1][0] = tmp[1].a[1][2] = 1;
    tmp[2].to_unit();
    tmp[2].a[0][1] = tmp[2].a[0][2] = 1;
    tmp[2].a[1][0] = tmp[2].a[1][2] = 1;
    vector<Info> ini(n + 1);
    for (int i = 1; i <= n; i++) {
        int type;
        if (s[i - 1] == '0') type = 0;
        else if (s[i - 1] == '1') type = 1;
        else type = 2;
        ini[i] = tmp[type];
    }
    seg.init(ini);
    while (qq--) {
        int ps;
        string s;
        cin >> ps >> s;
        int type;
        if (s[0] == '0') type = 0;
        else if (s[0] == '1') type = 1;
        else type = 2;
        seg.upd(ps, tmp[type]);
        auto& all = seg.seg[1];
        ll res = (all.a[0][2] + all.a[1][2]) % mod;
        cout << res << nl;
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