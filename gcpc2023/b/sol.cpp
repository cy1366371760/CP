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

pll operator -(pll a, pll b) {
    return pll(a.fi - b.fi, a.sc - b.sc);
}
ll cross(pll a, pll b) {
    return a.fi * b.sc - a.sc * b.fi;
}

void solve() {
    int n;
    cin >> n;
    vector<pll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].fi >> a[i].sc;
    }
    map<pair<int, vector<pll>>, bool> vis;
    auto dfs = [&](auto &&self, int dep, vector<pll> remain) -> void {
        if (vis.count(make_pair(dep, remain))) return;
        vis[make_pair(dep, remain)] = 1;
        if (remain.empty()) {
            cout << "possible" << nl;
            exit(0);
        }
        if (dep >= 4) return;
        if (remain.size() <= 2) {
            self(self, dep + 1, {});
            return;
        }
        int bound = min((int)remain.size(), 4);
        for (int i = 0; i < bound; i++) {
            for (int j = i + 1; j < bound; j++) {
                auto fir = remain[i];
                auto sec = remain[j];
                vector<pll> nxt;
                for (int k = 0; k < remain.size(); k++) {
                    if (k == i || k == j) continue;
                    ll res = cross(remain[k] - fir, remain[k] - sec);
                    if (res == 0) continue;
                    nxt.pb(remain[k]);
                }
                self(self, dep + 1, nxt);
            }
        }
    };
    dfs(dfs, 1, a);
    cout << "impossible" << nl;
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