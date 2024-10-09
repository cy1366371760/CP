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

const int MAX_SEG_V = 2e5 + 5;

template<class Info>
struct SegT {
	#define mid ((l + r) >> 1)
	#define ls(nw) seg[nw].ls
    #define rs(nw) seg[nw].rs
	#define nrs seg[nw].rs
	struct Node {
		int ls = 0, rs = 0;
		Info val;
	};
    vector<Node> seg;
    void init(int _sz) {
        seg.resize(_sz * 20 + 5);
    }
	int tot = 0;
	void push_up(int nw) {
		seg[nw].val = Info{};
		if (ls(nw)) seg[nw].val = seg[nw].val + seg[ls(nw)].val;
		if (rs(nw)) seg[nw].val = seg[nw].val + seg[rs(nw)].val;
	}
	int ins(int bf, int to, Info val, int l = 1, int r = MAX_SEG_V) {
		int nw = ++tot;
        seg[nw] = seg[bf];
		if (l == r) {
			seg[nw].val = seg[nw].val + val;
        //  cerr << l << ' ' << r << ' ' << nw << ' ' << seg[nw].val.v << '\n';
			return nw;
		}
		if (to <= mid) {
			ls(nw) = ins(ls(bf), to, val, l, mid);
		} else {
			rs(nw) = ins(rs(bf), to, val, mid + 1, r);
		}
		push_up(nw);
		return nw;
	}
	ll ask(int bf, int nw, int &need, int l, int r) {
		if (!nw || !need) return 0LL;
        auto cur = seg[nw].val - seg[bf].val;
        if (cur.c <= need) {
            need -= cur.c;
            return cur.sum;
        }
        if (l == r) {
            ll res = need * (cur.sum / cur.c);
            need = 0;
            return res;
        }
        ll res = ask(rs(bf), rs(nw), need, mid + 1, r);
        if (need) res += ask(ls(bf), ls(nw), need, l, mid);
        return res;
	}
    ll ask(int bf, int nw, int need) {
        int tmp = need;
		return ask(bf, nw, tmp, 1, MAX_SEG_V);
	}
	#undef mid
	#undef ls
	#undef rs
};
struct Info {
	int c = 0;
    ll sum = 0;
};
Info operator +(Info a, Info b) {
	return {a.c + b.c, a.sum + b.sum};
}
Info operator -(Info a, Info b) {
    return {a.c - b.c, a.sum - b.sum};
}

SegT<Info> seg;

void solve() {
    int n;
    cin >> n;
    vector<pll> vals(n);
    for (int i = 0; i < n; i++) {
        cin >> vals[i].fi >> vals[i].sc;
    }
    sort(all(vals), [](auto p, auto q) {
        return p.sc < q.sc;
    });
    vector<ll> buka;
    for (auto [a, b]: vals) buka.pb(a);
    buka.pb(-inf);
    sort(all(buka));
    buka.erase(unique(all(buka)), buka.end());
    for (int i = 0; i < n; i++) {
        // cerr << vals[i].fi << ' ' << vals[i].sc << '\n';
        vals[i].fi = lower_bound(all(buka), vals[i].fi) - buka.begin();
    }
    seg.init(n + 5);
    vector<int> rt(n + 1, 0);
    
    for (int i = 0; i < n; i++) {
        rt[i + 1] = seg.ins(rt[i], vals[i].fi, {1, buka[vals[i].fi]});
    }
    vector<ll> b(n + 1, 0);
    for (int i = 1; i <= n; i++) b[i] = vals[i - 1].sc;
    vector<ll> ans(n + 1, 0);
    auto dac = [&](auto &&self, int l, int r, int al, int ar) -> void {
        if (l > r) return;
        if (al == ar) {
            for (int i = l; i <= r; i++) {
                ans[i] = seg.ask(rt[0], rt[al], i) - b[al];
            }
            return;
        }
        int mid = (l + r) >> 1;
        int best = max(mid, al);
        ll best_val = seg.ask(rt[0], rt[best], mid) - b[best];
        for (int i = best + 1; i <= ar; i++) {
            ll val = seg.ask(rt[0], rt[i], mid) - b[i];
            if (val >= best_val) {
                best_val = val;
                best = i;
            }
        }
        ans[mid] = best_val;
        // cerr << "!!" << mid << ' ' << best << ' ' << best_val << '\n';
        self(self, l, mid - 1, al, best);
        self(self, mid + 1, r, best, ar);
    };
    dac(dac, 1, n, 1, n);
    for (int i = 1; i <= n; i++) {
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