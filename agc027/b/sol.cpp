#include<bits/stdc++.h>

#define nl '\n'
#define ll long long
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define eb emplace_back
#define fi first
#define sc second
#define int long long

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
    int n; ll X;
    cin >> n >> X;
    vector<ll> x(n + 5, 0LL);
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
    }
    ll l = 1, r = n;
    ll res = -1;
    auto chk = [&](ll tim) {
        vector<ll> ps(tim , 0);
        vector<ll> cost(tim, 1);
        int ptr = 0;
        ll res = 0;
        for (int i = n; i >= 1; i--) {
            int cur = ptr;
            ptr = (ptr + 1) % tim;
            res += cost[cur] * cost[cur] * abs(x[i] - ps[cur]);
            ++cost[cur];
            ps[cur] = x[i];
        }
        for (int i = 0; i < tim; i++) {
            res += ps[i] * cost[i] * cost[i];
        }
        res += (tim + n) * X;
        // if (res == 346) cerr << "GG" << tim << nl;
        return res;
    };
    while (l <= r) {
        ll dt = (r - l) / 3;
        ll lmid = l + dt;
        ll rmid = r - dt;
        ll lhs = chk(lmid);
        ll rhs = chk(rmid);
        if (res == -1) res = lhs;
        chkmin(res, lhs);
        chkmin(res, rhs);
        if (lhs <= rhs) {
            r = rmid - 1;
        } else {
            l = lmid + 1;
        }
    }
    cout << res << nl;
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