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

bool np[N];
int pri[N];
int pnum = 0;

bool use[3111][3111];

void solve() {
    int n;
    cin >> n;
    int need = 1;
    auto calc_mx = [&](int x) {
        if (x % 2 == 1) {
            return x * (x - 1) / 2 + x + 1;
        } else {
            int res = x * (x - 1) / 2 + x + 1;
            res -= (x - 2) / 2;
            return res;
        }
    };
    while (calc_mx(need) < n) {
        ++need;
    }
    if (need % 2 == 0) {
        for (int i = 2; i < need; i += 2) {
            use[i][i + 1] = use[i + 1][i] = 1;
        }
    }
    vector<int> res;
    auto dfs = [&](auto &&self, int x) -> void {
        for (int y = 0; y < need; y++) {
            if (!use[x][y]) {
                use[x][y] = 1;
                use[y][x] = 1;
                self(self, y);
            }
        }
        res.pb(x);
    };
    dfs(dfs, 0);
    assert(res.size() >= n);
    for (int i = 0; i < n; i++) {
        cout << pri[res[i]] << ' ';
    }
    cout << nl;
    // 1
    for (int i = 0; i < need; i++) {
        use[i][i + 1] = use[i + 1][i] = 0;
    }
    for (int i = 0; i + 1  < res.size(); i++) {
        use[res[i]][res[i + 1]] = use[res[i + 1]][res[i]] = 0;
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n = 1e6;
    for (int i = 2; i <= n; i++) {
        if (!np[i]) pri[++pnum] = i;
        for (int j = 1; j <= pnum && i * pri[j] <= n; j++) {
            np[i * pri[j]] = 1;
            if (i % pri[j] == 0) break;
        }
    }
    pri[0] = 1;
    int tt = 1;
    cin >> tt;
    while(tt--)
        solve();
    return 0;
}