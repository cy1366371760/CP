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
const int inf = 1e9;
const ll mod = 998244353;

const int bias = 1e5 + 5;
const int MAX_SEG_V = 5e5;

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
	Info ask(int bf, int nw, int L, int R, int l = 1, int r = MAX_SEG_V) {
		if (!nw) return Info{};
		if (l > R || r < L) {
			return Info{};
		}
		if (L <= l && r <= R) {
			return seg[nw].val - seg[bf].val;
		}
		return ask(ls(bf), ls(nw), L, R, l, mid) + ask(rs(bf), rs(nw), L, R, mid + 1, r);
	}
	#undef mid
	#undef ls
	#undef rs
};
struct Info {
	int v = 0;
};
Info operator +(Info a, Info b) {
	return {a.v + b.v};
}
Info operator -(Info a, Info b) {
    return {a.v - b.v};
}

SegT<Info> segT;

void solve() {
    int n;
    cin >> n;
    vector<pii> pt(n);
    for (int i = 0; i < n; i++) {
        cin >> pt[i].fi >> pt[i].sc;
        pt[i] = pii(pt[i].fi + pt[i].sc, pt[i].fi - pt[i].sc);
    }
    sort(all(pt));
    vector<int> rt(n + 1);
    segT.init((int)2e5);
    for (int i = 0; i < n; i++) {
        // cerr << "??" << pt[i].fi << ' ' << pt[i].sc << '\n';
        rt[i + 1] = segT.ins(rt[i], pt[i].sc + bias, {1});
    }
    int qq;
    cin >> qq;
    while (qq--) {
        int ox, oy, c;
        cin >> ox >> oy >> c;
        int x, y;
        x = ox + oy, y = ox - oy;
        int l = 0, r = 2e5, res = 2e5;
        while (l <= r) {
            int mid = (l + r) >> 1;
            int lb = lower_bound(all(pt), pii(x - mid, -inf)) - pt.begin();
            int rb = upper_bound(all(pt), pii(x + mid, inf)) - pt.begin() - 1;
            ++lb, ++rb;
            int cur = segT.ask(rt[lb - 1], rt[rb], max(1, y - mid + bias), y + mid + bias).v;
            // if (mid <= 5) {

            //     cerr << mid << ' ' << lb << ' ' << rb << ' ' << y - mid + bias << ' ' << y + mid + bias << '\n';
            // cerr << "fafa" << cur << '\n';
            // }
            if (cur >= c) {
                res = mid;
                r = mid - 1;
            } else l = mid + 1;
        }
        cout << res << '\n';
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