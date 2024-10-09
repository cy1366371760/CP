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
    vector<int> a(n);
    vector<int> b(m);
    vector<int> c;
    for (int i = 0; i < n; i++) cin >> a[i], c.pb(a[i]);
    for (int i = 0; i < m; i++) cin >> b[i], c.pb(b[i]);
    sort(all(a));
    sort(all(b));
    sort(all(c));
    map<int, int> ps;
    for (int i = 0; i < n + m; i++) ps[c[i]] = i;
    for (int i = 0; i < n; i++) {
        if (i + 1 < n) {
            int x = a[i];
            int y = a[i + 1];
            if (ps[x] + 1 == ps[y]) {
                cout << "Yes" << '\n';
                return;
            }
        }
    }
    cout << "No" << '\n';
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
