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

void solve() {
    int d;
    cin >> d;
    if (d <= 10) {
        cout << 57 << ' ' << 73 << ' ' << 97 << nl;
    } else {
        cout << 1 << ' ' << 2 << ' ' << 3 << nl;
    }
    // for (int a = 1; a <= 100; a++) {
    //     if (a == d) continue;
    //     for (int b = a + 1; b <= 100; b++) {
    //         if (b == d) continue;
    //         for (int c = b + 1; c <= 100; c++) {
    //             if (c == d) continue;
    //             vector<int> cur{a, b, c};
    //             bool gg = 0;
    //             vector<int> op(4, 0);
    //             iota(all(op), 0);
    //             vector<int> order(3, 0);
    //             iota(all(order), 0);
    //             do {
    //                 do {
    //                     vector<double> res;
    //                     for (int i = 0; i < 3; i++) {
    //                         if (res.empty()) {
    //                             res.pb(cur[order[i]]);
    //                         } else {
    //                             double u = res.back();
    //                             double v = cur[order[i]];
    //                             if (op[i - 1] == 0) u += v;
    //                             else if (op[i - 1] == 1) u -= v;
    //                             else if (op[i - 1] == 2) u *= v;
    //                             else if (op[i - 1] == 3) u = 1.0 * u / v;
    //                             res.pb(u);
    //                         }
    //                     }
    //                     for (int i = 0; i < 3; i++) {
    //                         if (res[i] == d) {
    //                             gg = 1;
    //                             break;
    //                         }
    //                     }
    //                 } while(next_permutation(all(op)));
    //                 if (gg) break;
    //             } while (next_permutation(all(order)));
    //             if (!gg) {
    //                 cout << a << ' ' << b << ' ' << c << nl;
    //                 return;
    //             }
    //         }
    //     }
    // }
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