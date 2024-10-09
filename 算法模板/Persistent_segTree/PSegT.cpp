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