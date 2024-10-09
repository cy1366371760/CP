#include <bits/stdc++.h>

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
template <typename T>
bool chkmin(T &a, T b) { return (b < a) ? a = b, 1 : 0; }
template <typename T>
bool chkmax(T &a, T b) { return (b > a) ? a = b, 1 : 0; }
using namespace std;
using ld = long double;
const int N = 1e6 + 100;
const ll inf = 1e18;
const ll mod = 998244353;
#define int long long
/*

[l, mid, r]

[l - 1, mid - 1] sel L
[mid, r] sel R
pre[R] - pre[L] <= S - v

pre[R] <= pre[L] + S - v
pre[L] >= pre[R] - (S - v)

dac(l, r)

min_ps

big side

*/

void solve() {
    int n;
    ll S;
    cin >> n >> S;
    vector<ll> a(n + 2), b(n + 2);
    vector<ll> pre(n + 2);
    vector<ll> buk;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        pre[i] = pre[i - 1] + b[i];
    }
    buk.pb(-1e18);
    for (int i = 0; i <= n; i++) {
        buk.pb(pre[i]);
    }
    buk.erase(unique(all(buk)), buk.end());
    for (int i = 0; i <= n; i++) {
        pre[i] = lower_bound(all(buk), pre[i]) - buk.begin();
    }
    const int M = 20;
    vector ST(M, vector<pll>(n + 2));
    vector<int> lg(n + 2, 0);
    for (int i = 1; i <= n; i++) {
        ST[0][i] = pll(a[i], i);
        if (i > 1) {
            lg[i] = lg[i >> 1] + 1;
        }
    }
    for (int j = 1; j < M; j++) {
        int len = (1 << j);
        int half = len >> 1;
        for (int i = 1; i + len - 1 <= n; i++) {
            ST[j][i] = ST[j - 1][i];
            chkmin(ST[j][i], ST[j - 1][i + half]);
        }
    }
    auto ask_min = [&](int l, int r) {
        int len = (r - l + 1);
        int k = lg[len];
        return min(ST[k][l], ST[k][r - (1 << k) + 1]);
    };
    ll ans = 0;
    int LIM = buk.size();
    vector<int> fen(LIM + 100, 0);
    auto add = [&](int x, int y) {
        for (; x <= LIM; x += x & -x) fen[x] += y;
    };
    auto ask = [&](int x) {
        if (x < 0) return 0LL;
        ll res = 0;
        for (; x; x -= x & -x) res += fen[x];
        return res;
    };
    auto dac = [&](auto &&self, int l, int r) -> void { // pre[l]... pre[r] stored when end
        if (l > r) return;
        auto [mn_val, mn_ps] = ask_min(l, r);
        ll bf = ans;
        // cerr << l << ' ' << r << ' ' << mn_ps << nl;
        if (mn_ps - l <= r - mn_ps) {
            self(self, l, mn_ps - 1);
            for (int i = l; i < mn_ps; i++) {
                add(pre[i], -1);
            }
            self(self, mn_ps + 1, r); // mn_ps + 1, r
            add(pre[mn_ps], 1);
            for (int i = l; i <= mn_ps; i++) {
                ll val = buk[pre[i - 1]] + S - mn_val;
                ll tmp = val;
                val = lower_bound(all(buk), val) - buk.begin();
                if (val == buk.size() || buk[val] > tmp) --val;
                ans += ask(val);
            }
            for (int i = l; i < mn_ps; i++) {
                add(pre[i], 1);
            }
        } else {
            self(self, mn_ps + 1, r);
            for (int i = mn_ps + 1; i <= r; i++) {
                add(pre[i], -1);
            }
            self(self, l, mn_ps - 1);
            add(pre[l - 1], 1);
            for (int i = mn_ps; i <= r; i++) {
                ll val = buk[pre[i]] - (S - mn_val);
                val = lower_bound(all(buk), val) - buk.begin();
                ans += (mn_ps - l + 1) - ask(val - 1);
            }
            add(pre[l - 1], -1);
            for (int i = mn_ps; i <= r; i++) {
                add(pre[i], 1);
            }
        }
        // cerr << "GG: " << l << ' ' << r << ' ' << ans - bf << nl;
    };
    dac(dac, 1, n);
    cout << ans << nl;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    // int tt = 1;
    // cin >> tt;
    // while (tt--)
        solve();
    return 0;
}