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
const int N = 2050;
const ll inf = 1e18;
const ll mod = 998244353;

void solve() {
    int n, L, R;
    cin >> n >> L >> R;
    vector<int> dp(n + 5, 0);
    vector who(n + 5, vector<pii> (n + 5));
    vector laz(n + 5, vector<array<int, 4>>());
    vector <array<int, 3>> hav(n + 5);
    for (int i = 0; i <= n; i++) {
        hav[i] = {-1, 0, 0};
    }
    for (int i = 0; i <= n; i++) {
        dp[i] = n + 1;
        for (auto [tr, val, fir, sec] : laz[i]) {
            chkmax(hav[val], {tr, fir, sec});
            // cerr << "!!" << i << ' ' << tr << ' ' << val << ' ' <<fir << ' ' << sec << '\n';
            // cerr << "fafa" << hav[val][0] << ' ' << hav[val][1] << ' ' << hav[val][2] <<'\n';
        }
        for (int j = 0; j <= n; j++) {
            if (hav[j][0] >= i) {
                who[i][j] = pii(hav[j][1], hav[j][2]);
                // cerr << "gg" << i << ' ' <<j << ' ' << who[i][j].fi<<'\n';
                continue;
            }
            dp[i] = j;
            break;
        }
        // cerr<< "fuck" << i << ' ' << dp[i] << '\n';
        for (int bf = 0; bf <= i; bf++) {
            int tl = bf + i + L;
            int tr = bf + i + R;
            if (tl <= n) {
                laz[tl].pb({tr, dp[bf] ^ dp[i], bf, i});
            }
        }
    }
    int sta = dp[n];
    vector<pii> segs;
    segs.eb(1, n);
    auto upd = [&](int l, int r) {
        vector<pii> nxt;
        for (auto [cl, cr] : segs) {
            if (cr < l || cl > r) {
                nxt.eb(cl, cr);
                continue;
            }
            assert(cl <= l && r <= cr);
            sta ^= dp[cr - cl + 1];
            if (cl < l) {
                nxt.eb(cl, l - 1);
                sta ^= dp[l - 1 - cl + 1];
            }
            if (cr > r) {
                nxt.eb(r + 1, cr);
                sta ^= dp[cr - (r + 1) + 1];
            }
        }
        swap(segs, nxt);
    };
    auto judge = [&]() {
        int l, r;
        cin >> l >> r;
        if (l == 0 && r == 0) {
            exit(0);
        }
        r = l + r - 1;
        upd(l, r);
    };
    if (sta == 0) {
        cout << "Second" << endl;
        judge();
    } else {
        cout << "First" << endl;
    }
    while (1) {
        assert(sta != 0);
        // cerr << "PP" << sta << '\n';
        for (auto [cl, cr] : segs) {
            int len = cr - cl + 1;
            int need = sta ^ dp[len];
            // cerr << "fafa" << ' ' << cl << ' ' << cr << '\n';
            if (need < dp[len]) {
                auto [fir, sec] = who[len][need];
                int del = len - fir - sec;
                // cerr << len << ' ' << need << ' ' << ' ' << fir << ' ' << sec << ' ' << del << '\n';
                assert(L <= del && del <= R); 
                cout << cl + fir << ' ' << del << endl;
                upd(cl + fir, cl + fir + del - 1);
                break;
            }
        }
        assert(sta == 0);
        judge();
    }
}

signed main() {
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    // int tt = 1;
    // cin >> tt;
    // while(tt--)
        solve();
    return 0;
}