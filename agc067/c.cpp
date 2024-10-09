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

int pri[N];
bool np[N];
int pnum = 0;

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n + 5);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    bool gg = 0;
    for (int i = 1; i <= n && !gg; i++) {
        for (int j = i + 1; j <= n && !gg; j++) {
            if (j % i == 0) {
                if (a[j] % a[i]) gg = 1;
            } else {
                if (a[j] % a[i] == 0) gg = 1;
            }
        }
    }
    for (int p = 1; p <= pnum && pri[p] <= n; p++) {
        int nw = pri[p];
        while (1LL * nw * pri[p] <= n) nw *= pri[p];
        vector<bool> vis(n + 5, 0);
        int old_mn = 1e9;
        for (int i = nw; i >= 1; i /= pri[p]) {
            int mn = 1e9, mx = -1e9;
            for (int j = i; j <= n; j += i) {
                if (vis[j]) continue;
                int cur = 0;
                ll val = a[j];
                while (val % pri[p] == 0) val /= pri[p], cur++;
                chkmin(mn, cur), chkmax(mx, cur);
                vis[j] = 1;
            }
            if (mx >= old_mn) gg = 1;
            old_mn = mn;
        }
    }
    cout << (gg ? "No" : "Yes") << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n = 5050;
    for (int i = 2; i <= n; i++) {
        if (!np[i]) pri[++pnum] = i;
        for (int j = 1; j <= pnum && i * pri[j] <= n; j++) {
            np[i * pri[j]] = 1;
            if (i % pri[j] == 0) break;
        }
    }
    int tt = 1;
    cin >> tt;
    while(tt--)
        solve();
    return 0;
}