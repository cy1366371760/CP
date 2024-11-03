#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fi first
#define sc second
#define pb push_back
#define all(x) x.begin(),x.end()
#define nl '\n'
using namespace std;
const ll inf = 1e18;
const int N = 1e6 + 100;

int fa[N];

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;
    fa[x] = y;
}

ll exgcd(ll a, ll b, ll &x, ll &y) {
    ll d = a;
    if (b) {
        d = exgcd(b, a % b, x, y);
        x -= (a / b) * y;
        swap(x, y);
    } else {
        x = 1, y = 0;
    }
    return d;
}

ll calc(ll k, ll n) {
    ll a, b;
    exgcd(k, n, a, b);
    return (a % n + n) % n;
}

void solve() {
    int n, qq;
    cin >> n >> qq;
    vector<ll> a(n);
    vector<ll> order(n);
    vector<ll> still(n);
    for (int i = 0; i < n; i++) {
        a[i] = i;
        order[i] = i;
        still[i] = i;
        fa[i] = i;
    }
    ll k = 1, b = 0;
    ll remain = n;
    auto dis = [&](ll i, ll j) -> ll {
        ll res = j - i;
        if (res < 0) res += n;
        return res;
    };
    auto doit = [&](ll k, ll b, ll d) {
        vector hav(n, vector<pll>());
        for (int i = 0; i < n; i++) {
            if (a[i] == -1) continue;
            ll to = (i * k + b) % n * d % n;
            hav[to].pb({dis(i, to), a[i]});
        }
        order.clear();
        still.clear();
        order.resize(n);
        still.resize(remain);
        int ptr = 0;
        for (int i = 0; i < n; i++) {
            if (!hav[i].size()) {
                a[i] = -1;
                continue;
            }
            pll tmp = *min_element(all(hav[i]));
            for (auto [_, who] : hav[i]) {
                merge(who, tmp.sc);
            }
            a[i] = tmp.sc;
            still[ptr] = a[i];
            order[a[i]] = ptr;
            ptr++;
        }
    };
    ll only_who = -1, only_ps = -1;
    for (int i = 1; i <= qq; i++) {
        string s;
        ll d;
        cin >> s >> d;
        if (d == n) d = 0;
        // cerr << "!!" << s << ' ' << d << nl;
        if (s == "+") {
            b = (b + d) % n;
        } else if (s == "*") {
            ll g = __gcd(d, remain);
            if (g == 1) {
                k = k * d % n;
                b = b * d % n;
            } else {
                remain /= g;
                doit(k, b, d);
                k = 1, b = 0;
            }
        } else {
            if (remain == 1) {
                ll nw = (only_ps * k + b) % n;
                if (nw == d) {
                    cout << only_who << nl;
                } else {
                    cout << -1 << nl;
                }
                continue;
            }
            ll want = (d - b + n) % n;
            if (a[want] == -1) {
                cout << -1 << nl;
                return;
            }
            ll fafa = order[want];
            ll kinv = calc(k % remain, remain);
            // cerr << "GG" << kinv << nl;
            ll x = fafa * kinv % remain;
            ll res = still[x];
            if (res == 0) cout << n << nl;
            else cout << res << nl;
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
}