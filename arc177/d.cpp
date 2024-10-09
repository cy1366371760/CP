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

ll qpow(ll x, ll y = mod - 2) {
    ll res = 1;
    x %= mod;
    while (y) {
        if (y & 1) {
            res = res * x % mod;
        }
        x = x * x % mod;
        y >>= 1;
    }
    return res;
}

ll inv2[N];

void solve() {
    int n;
    ll h;
    cin >> n >> h;
    vector<pll> a(n);
    inv2[0] = 1;
    inv2[1] = qpow(2);
    for (int i = 0; i < n; i++) {
        cin >> a[i].fi;
        a[i].sc = i;
    }
    for (int i = 1; i <= n + 5; i++) {
        inv2[i] = inv2[i - 1] * inv2[1] % mod;
    }
    sort(all(a));
    auto doit = [&](vector<ll> cur, int index) {
        int n = cur.size();
        vector<pll> order;
        for (int i = 0; i < cur.size(); i++) {
            order.pb(pll(cur[i], i));
        }
        sort(all(order));

        vector<bool> ocr(n, 0);
        ll cur_p = 0;
        vector<array<ll, 3>> res;
        set<pll> dp_l, dp_r;
        dp_l.insert(pll(-inf, 1));
        dp_r.insert(pll(-inf, 1));
        for (int i = 0; i < n; i++) {
            ll who = order[i].sc;
            ll tim = order[i].fi;
            ll tmp = 1;
            ll lhs = (*prev(dp_l.upper_bound(pll(who, 0)))).sc;
            tmp = tmp * lhs % mod;
            ll rhs = (*prev(dp_r.upper_bound(pll(-who, 0)))).sc;
            tmp = tmp * rhs % mod;
            dp_l.insert(pll(who, lhs * inv2[1] % mod));
            dp_r.insert(pll(-who, rhs * inv2[1] % mod));
            ll p = 0;
            if (who == 0 || who > 0 && ocr[who - 1]) {
                p = (p + tmp * inv2[1]) % mod;
            }
            if (who == n - 1 || who < n - 1 && ocr[who + 1]) {
                p = (p + tmp * inv2[1]) % mod;
            }
            cur_p = (cur_p + p) % mod;
            // cerr << who << ' ' << tim << ' ' << p << '\n';
            ocr[who] = 1;
            res.pb({tim, index, cur_p});
        }
        return res;
    };
    int index = 0;
    vector<array<ll, 3>> ans;
    for (int i = 0; i < n; i++) {
        ll rb = a[i].fi + h;
        int j = i;
        while (j < n && a[j].fi <= rb) {
            rb = a[j].fi + h;
            j++;
        }
        --j;
        // cerr << "!!" << i << ' ' << j << '\n';
        vector<ll> cur;
        for (int k = i; k <= j; k++) {
            cur.pb(a[k].sc);
        }
        auto res = doit(cur, index);
        for (auto [tim, index, p] : res) {
            ans.pb({tim, index, p});
        }
        index++;
        i = j;
    }
    sort(all(ans));
    // cerr << "fuck" << index << '\n';
    {
        ll res = 1;
        ll zeros = index;
        ll bf = 0;
        vector<ll> cur(index + 5, 0);
        int ptr = 0;
        assert(ans.size() == n);
        for (auto[tim, i, p]: ans) {
            if (cur[i] == 0) {
                zeros--;
            } else {
                res = res * qpow(cur[i]) % mod;
            }
            cur[i] = p;
            if (p != 0) res = res * p % mod;
            else zeros++;
            ++ptr;
            ll ccc;
            if (!zeros) {
                ccc = res * qpow(2, n) % mod;
            } else {
                ccc = 0;
            }
            cout << (ccc - bf + mod) % mod << ' ';
            bf = ccc;
        }
        cout << '\n';
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
