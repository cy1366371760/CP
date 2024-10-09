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

void Add(ll &x, ll y) {
    x = (x + y) % mod;
}
void Sub(ll &x, ll y) {
    x = (x - y % mod + mod) % mod;
}

void solve() {
    ll n;    
    cin >> n;
    vector a(2, vector<ll>(n + 5, 0LL));
    for (int nw = 0; nw < 2; nw++) {
        for (int i = 1; i <= n; i++) {
            cin >> a[nw][i];
        }
    }
    ll ans = 0;
    auto dac = [&](auto &&self, int l, int r) -> pair<vector<vector<vector<ll>>>, vector<vector<vector<ll>>>> {
        int len = r - l + 1;
        vector dp_l(2, vector(2, vector<ll>(len, 0)));
        auto dp_r = dp_l;
        if (l == r) {
            dp_l[0][0][0] = a[0][l];
            dp_l[0][1][0] = dp_l[1][0][0] = a[0][l] + a[1][l];
            dp_l[1][1][0] = a[1][l];
            dp_r = dp_l;
            Add(ans, 3LL * (a[0][l] + a[1][l]));
            return make_pair(dp_l, dp_r);
        }
        int mid = (l + r) >> 1;
        auto [lhs_dp_l, lhs_dp_r] = self(self, l, mid);
        auto [rhs_dp_l, rhs_dp_r] = self(self, mid + 1, r);
        int lsize = (mid - l + 1);
        int rsize = (r - mid);
        vector<pll> lhs_buk, rhs_buk;
        for (int nw = 0; nw < 2; nw++) {
            for (int i = 0; i < lsize; i++) {
                lhs_buk.pb({lhs_dp_r[nw][0][i], lhs_dp_r[nw][1][i]});
            }
            for (int i = 0; i < rsize; i++) {
                rhs_buk.pb({rhs_dp_l[nw][0][i], rhs_dp_l[nw][1][i]});
            }
        }
        sort(all(lhs_buk), [&](auto u, auto v) {
            return u.sc - u.fi < v.sc - v.fi;
        });
        sort(all(rhs_buk), [&](auto u, auto v) {
            return u.fi - u.sc < v.fi - v.sc;
        });
        ll rptr = 0;
        ll sum_C = 0, sum_D = 0;
        for (auto [B, D] : rhs_buk) Add(sum_D, D);
        for (int i = 0; i < lhs_buk.size(); i++) {
            auto [A, B] = lhs_buk[i];
            while (rptr < rhs_buk.size()) {
                auto [C, D] = rhs_buk[rptr];
                if (B - A >= C - D) {
                    Add(sum_C, C % mod);
                    Sub(sum_D, D % mod);
                    ++rptr;
                } else break;
            }
            Add(ans, sum_C + A % mod * rptr % mod);
            Add(ans, sum_D + B % mod * (rhs_buk.size() - rptr) % mod);
        }
        // dp_l
        for (int i = 0; i < lsize; i++) {
            for (int nw = 0; nw < 2; nw++) {
                for (int to = 0; to < 2; to++) {
                    dp_l[nw][to][i] = lhs_dp_l[nw][to][i];
                }
            }
        }
        for (int i = 0; i < rsize; i++) {
            int idx = lsize + i;
            for (int nw = 0; nw < 2; nw++) {
                for (int to = 0; to < 2; to++) {
                    ll cost = -1;
                    for (int mid = 0; mid < 2; mid++) {
                        ll cur = rhs_dp_l[nw][mid][i] + lhs_dp_l[mid][to][lsize - 1];
                        if (cost == -1 || cost > cur) cost = cur;
                    }
                    dp_l[nw][to][idx] = cost;
                }
            }
        }
        // dp_r
        for (int i = 0; i < rsize; i++) {
            int idx = lsize + i;
            for (int nw = 0; nw < 2; nw++) {
                for (int to = 0; to < 2; to++) {
                    dp_r[nw][to][idx] = rhs_dp_r[nw][to][i];
                }
            }
        }
        for (int i = 0; i < lsize; i++) {
            for (int nw = 0; nw < 2; nw++) {
                for (int to = 0; to < 2; to++) {
                    ll cost = -1;
                    for (int mid = 0; mid < 2; mid++) {
                        ll cur = lhs_dp_r[nw][mid][i] + rhs_dp_r[mid][to][0];
                        if (cost == -1 || cost > cur) cost = cur;
                    }
                    dp_r[nw][to][i] = cost;
                }
            }
        }
        return make_pair(dp_l, dp_r);
    };
    dac(dac, 1, n);
    ll extra = ans;
    for (int i = 1; i <= n; i++) {
        Sub(extra, (3LL * a[0][i] + 3LL * a[1][i]) % mod);
    }
    Add(ans, extra);
    cout << ans << nl;
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