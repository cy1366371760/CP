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
const int N = 310;
const ll inf = 1e18;
const ll mod = 998244353;

using BST = bitset<310>;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<ll> pw2(n + m + 5, 0);
    pw2[0] = 1;
    for (int i = 1; i < pw2.size(); i++) {
        pw2[i] = pw2[i - 1] * 2 % mod;
    }
    vector a(n, BST());
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x;
            cin >> x;
            a[i][j] = x;
        }
    }
    vector<BST> bas(m);
    vector<bool> vis(m, 0);
    int out = 0;
    for (int i = 0; i < n; i++) {
        auto vec = a[i];
        bool used = 0;
        for (int j = 0; j < m; j++) {
            if (vec[j] == 0) continue;
            if (!vis[j]) {
                vis[j] = 1;
                bas[j] = vec;
                used = 1;
                break;
            } else {
                vec ^= bas[j];
            }
        }
        if (!used) {
            out++;
        }
    }
    ll ans = (pw2[n] - pw2[out] + mod) % mod;
    ans = ans * pw2[m - 1] % mod;
    cout << ans << '\n';
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