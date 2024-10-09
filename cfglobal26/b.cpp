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
    ll x;
    cin >> x;
    vector<ll> a;
    while (x) {
        a.pb(x % 10);
        x /= 10;
    }
    int m = 0;
    if (a.back() > 1) {
        cout << "NO\n";
        return;
    } else {
        m = a.size() - 1;
    }
    bool low = 1, up = 0;
    for (int i = 0; i < m; i++) {
        bool nlow = 0, nup = 0;
        for (int x = 5; x <= 9; x++) {
            for (int y = 5; y <= 9; y++) {
                if (low && (x + y) % 10  == a[i]) {
                    nup = 1;
                }
                if (up && (x + y + 1) % 10  == a[i]) {
                    nup = 1;
                }
            }
        }
        low = nlow;
        up = nup;
    }
    cout << (up ? "YES" : "NO") << '\n';
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
