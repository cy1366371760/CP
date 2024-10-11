#include<bits/stdc++.h>

using namespace std;
#define ll long long
#define nl '\n'
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define ii pair<ll, ll>


const ll mod = 1e9 + 7;
ll n, m, d0, d1, d2;
vector<string> grid;

vector<ii> edges{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
vector<ii> corners{{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

ll qpow(ll x, ll y = mod - 2) {
    ll res = 1;
    while (y) {
        if (y & 1) res = res * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return res;
}

ll inv2 = qpow(2);

ll calcexp(int i, int j) {
    ll ans = 0;
    if (grid[i][j] == 'V') return d0;
    ll probs_center = 1;
    if (grid[i][j] == '?') {
        probs_center = probs_center * inv2 % mod;
    }
    probs_center = (1LL - probs_center + mod) % mod;
    ans = (ans + d0 * probs_center) % mod;
    ll probs_not_edge = 1;
    for (auto &[di, dj]:edges) {
        if (i+di < 0 || i + di >= n || j+dj < 0  || j + dj >= m) continue;
        if (grid[i+di][j+dj] == 'V') return (d1 * (1LL-probs_center + mod) % mod + ans) % mod;
        if (grid[i+di][j+dj] == '?') {
            probs_not_edge = probs_not_edge * inv2 % mod;
        }
    }
    ll probs_edge = (1LL - probs_not_edge + mod) % mod;
    ans = (ans + (1LL - probs_center + mod) * (probs_edge) % mod * d1 % mod) % mod;

    ll probs_not_corner = 1;
    for (auto &[di, dj]: corners) {
        if (i+di < 0 || i + di >= n || j+dj < 0  || j + dj >= m) continue;
        if (grid[i+di][j+dj] == 'V') return (d2 * (1LL-probs_center + mod) % mod * (1LL-probs_edge + mod) % mod + ans) % mod;
        if (grid[i+di][j+dj] == '?') {
            probs_not_corner = probs_not_corner * inv2 % mod;
        }
    }
    
    ans = (ans + (1LL - probs_center + mod) % mod * (1LL - probs_edge + mod) % mod * (1LL - probs_not_corner + mod) % mod * d2 % mod) % mod;
    return ans;
}


void solve() {
    cin >> n >> m >> d0 >> d1 >> d2;
    grid.resize(n);
    for (int i=0;i<n;i++) cin >> grid[i];
    ll ans = 0;
    // for (int i=0;i<n;i++) for (int j=0;j<m;j++) ans += calcexp(i, j);
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<m; j++) {
            ans = (ans + calcexp(i, j)) % mod;
        }
    }
    // cout<<ans<<nl;
   cout << ans << nl;
    
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}