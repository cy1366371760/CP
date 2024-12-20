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
    int n;
    cin >> n;
    vector<ll> a(n + 5, 0);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    cout << "Yes" << '\n';
    vector<bool> use(n + 5, 0);
    vector<pii> res;
    for (int val = n - 1; val >= 1; val--) {
        vector<int> las(val + 1, -1);
        for (int i = 1; i <= n; i++) {
            if (use[i]) {
                continue;
            }
            int nw = a[i] % val;
            if (las[nw] != -1) {
                res.eb(i, las[nw]);
                use[i] = 1;
                break;
            } else {
                las[nw] = i;
            }
        }
    }
    reverse(all(res));
    for (auto [x, y] : res) {
        cout << x << ' ' << y << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--)
        solve();
    return 0;
}
