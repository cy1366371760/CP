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

void solve() {
    int n, m;
    cin >> n >> m;
    vector<ll> pos, neg;
    for (int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        if (x <= 0) {
            neg.pb(x);
        } else {
            pos.pb(x);
        }
    }
    sort(all(pos)), sort(all(neg));
    if (m > n) {
        cout << -1 << nl;
        return;
    }
    ll zero_ok = 0;
    if (pos.size() == m) {
        cout << 0 << nl;
        return;
    } else if (pos.size() < m) {
        if (pos.size() == 0) {
            cout << -1 << nl;
            return;
        }
    } else {
        int real_neg = 0;
        for (auto x : neg) {
            if (x < 0) ++real_neg;
        }
        if (real_neg == 0) {
            cout << -1 << nl;
            return;
        }
        swap(pos, neg);
        for (auto &val : pos) val = -val;
        for (auto &val : neg) val = -val;
        reverse(all(pos)), reverse(all(neg));
        m = n - m;
        zero_ok = 1;
    }
    m -= pos.size();
    reverse(all(neg));
    while (neg.size() > m) neg.pop_back();
    reverse(all(neg));
    ll extra = 0, ans = 4e18;
    auto doit = [&](ll val, ll dt) {
        ll need = abs(val) + (zero_ok ? 0 : 1);
        need = (need + dt - 1) / dt;
        return pll(need, val + need * dt); 
    };
    if (pos.size() == 1) {
        --m;
        ll nw = neg.back();
        neg.pop_back();
        auto [need, to] = doit(nw, pos[0]);
        extra += need;
        pos.push_back(to);
        sort(all(pos));
    }
    vector<pll> dp;
    dp.pb({pos.end()[-2], pos.end()[-1]});
    while (dp.back().sc < (1 - zero_ok) + abs(neg[0])) {
        pll nxt = {dp.back().sc, dp.back().fi + dp.back().sc};
        dp.pb(nxt);
    }
    vector<ll> cost(dp.size(), 0);
    int maybe = 0;
    for (int i = neg.size() - 1; i >= 0; i--) {
        int nxt_maybe = maybe;
        for (int use = dp.size() - 1; use >= maybe; use--) {
            ll val = dp[use].sc;
            auto [need, to] = doit(neg[i], val);
            if (need > 1) {
                cost[use] += need;
                if (need >= 5) {
                    nxt_maybe = max(maybe, use + 1);
                }
                chkmin(cost[use], (ll)4e18);
            } else {
                cost[use] += 1;
                pll achieve = pll(min((ll)4e18, dp[use].sc), min((ll)4e18, 2LL * dp[use].sc + neg[i]));

                if (use < dp.size() - 1 && achieve > dp[use + 1]) {
                    dp[use + 1] = achieve;
                }
            }
        }
        maybe = nxt_maybe;
    }
    for (int i = maybe; i < dp.size(); i++) {
        chkmin(ans, extra + i + cost[i]);
    }
    cout << ans << nl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--)
        solve();
    return 0;
}