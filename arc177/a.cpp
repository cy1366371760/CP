#include<bits/stdc++.h>

#define ll long long
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define eb emplace_back
#define fi first
#define sc second

#define pll pair<ll, ll>
template<typename T> bool chkmin(T &a, T b){return (b < a) ? a = b, 1 : 0;}
template<typename T> bool chkmax(T &a, T b){return (b > a) ? a = b, 1 : 0;}
using namespace std;
using ld = long double;
const int N = 1e6 + 100;
const ll inf = 1e18;
const ll mod = 998244353;

void solve() {
    int a, b, c, d, e, f, n;
    cin >> a >> b >> c >> d >> e >> f >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++)
        cin >> v[i];
    bool flg = 1;
    for (int i = 0; i < n; i++) {
        int nw = v[i];
        while (nw >= 500 && f >= 1) {
            nw -= 500, f--;
        }
        while (nw >= 100 && e >= 1) {
            nw -= 100, e--;
        }
        while (nw >= 50 && d >= 1) {
            nw -= 50, d--;
        }
        while (nw >= 10 && c >= 1) {
            nw -= 10, c--;
        }
        while (nw >= 5 && b >= 1) {
            nw -= 5, b--;
        }
        while (nw >= 1 && a >= 1) {
            nw -= 1, a--;
        }
        if (nw) {
            flg = 0;
            break;
        }
    }
    cout << (flg ? "Yes" : "No") << '\n';
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
