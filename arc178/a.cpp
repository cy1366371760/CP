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

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }
    sort(all(a));
    if (a[0] == 1 || a[m - 1] == n) {
        cout << -1 << '\n';
        return;
    }
    vector<bool> vis(n + 1, 0);
    vis[0] = 1;
    int p = 0, hed = 0;
    for (int i = 1; i <= n; i++) {
        while (hed < m && a[hed] < i) {
            ++hed;
        }
        if (hed < m && a[hed] == i) {
            cout << i + 1 << ' ';
            vis[i + 1] = 1;
            continue;
        }
        while (vis[p]) {
            ++p;
        }
        cout << p << ' ';
        vis[p] = 1;
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
