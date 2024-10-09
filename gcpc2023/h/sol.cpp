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
const ll mod = 1e9 + 7;
const ll g = 5;

// 5e8 + 
ll qpow(ll x, ll y = mod - 2) {
    ll res = 1;
    while (y) {
        if (y & 1) res = res * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return res;
}

void solve() {
    ll n;
    cin >> n;
    if (n == 0) {
        cout << ".##" << nl << "##." << nl;
        return;
    }
    if (n == 1) {
        cout << "." << nl << "." << nl;
        return;
    }
    vector<ll> fib(110, 0);
    vector<ll> ifib(110, 0);
    fib[1] = 1;
    fib[2] = 1;
    ifib[1] = ifib[2] = 1;
    for (int i = 3; i <= 100; i++) {
        fib[i] = (fib[i - 1] + fib[i - 2]) % mod;
        ifib[i] = qpow(fib[i]);
    }
    map<ll, vector<int>> vis;
    vector<int> cur;
    ll sz = 0, val = n;
    int need = 1000000;
    auto dfs = [&](auto &&self, int i) {
        if (vis.size() >= need) return;
        if (!vis.count(val)) {
            vis[val] = cur;
        }
        if (i + sz <= 100) {
            self(self, i + 1);
        }
        auto bf = cur;
        int bf_sz = sz;
        ll bf_val = val;
        while (sz + i <= 100) {
            val = val * ifib[i] % mod;
            sz += i;
            cur.pb(i);
            self(self, i + 1);
        }
        cur = bf, sz = bf_sz, val = bf_val;
    };
    dfs(dfs, 2);
    {
        ll val = 1, sz = 0;
        vector<int> cur;
        map<pair<ll, int>, bool> ocr;
        auto output = [&](vector<int> fir, vector<int> sec) {
            fir.insert(fir.end(), all(sec));
            for (int t = 0; t < 2; t++) {
                for (int x : fir) {
                    for (int j = 1; j < x; j++) {
                        cout << '.';
                    }
                    cout << '#';
                }
                cout << nl;
            }
        };
        auto dfs = [&](auto &&self, int i) {
            if (ocr.count(pll(val, i))) return;
            ocr[pll(val, i)] = 1;
            if (vis.count(val)) {
                output(vis[val], cur);
                exit(0);
            }
            auto bf = cur;
            ll bf_sz = sz;
            ll bf_val = val;
            while (sz + i <= 100) {
                val = val * fib[i] % mod;
                sz += i;
                cur.pb(i);
                self(self, i + 1);
            }
            cur = bf, sz = bf_sz, val = bf_val;
        };
        dfs(dfs, 2);
        //
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