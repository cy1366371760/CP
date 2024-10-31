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
const ld pi = acos(-1);

void solve() {
    int n;
    cin >> n;
    vector<ld> lo(n), la(n);
    vector<int> ang_lo(n), ang_la(n);
    for (int i = 0; i < n; i++) {
        cin >> ang_la[i] >> ang_lo[i];
        la[i] = ang_la[i], lo[i] = ang_lo[i];
        la[i] = la[i] / 180.0 * pi;
        lo[i] = lo[i] / 180.0 * pi;
    }
    map<double, bool> vis;
    for (int a = 0; a < n; a++) {
        int b = (a + 1) % n;
        if (ang_la[a] + 180 == ang_la[b] || ang_la[a] - 180 == ang_la[b]) {
            cout << "yes" << nl;
            return;
        }
        ld tmp = ang_lo[b] - ang_lo[a];
        if (tmp < 0) tmp = 180 - ang_lo[a] + ang_lo[b] + 180;
        if (tmp <= 180) {
            for (ld x = ang_lo[a]; ; x += 0.5) {
                if (x == 180) x = -180;
                vis[x] = 1;
                if (x == (ld)ang_lo[b]) {
                    break;
                }
            }
        } else {
            for (ld x = ang_lo[a]; ; x -= 0.5) {
                if (x == -180.5) x = 179.5;
                vis[x] = 1;
                if (x == (ld)ang_lo[b]) {
                    break;
                }
            }
        }
    }
    for (ld a = -180; a < 180; a += 0.5) {
        if (!vis.count(a)) {
            cout << "no " << fixed << setprecision(1) << a << nl;
            return;
        }
    }
    cout << "yes" << nl;
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