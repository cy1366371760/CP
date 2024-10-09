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
    int w, h;
    cin >> w >> h;
    vector<int> rem(w + 5, 0);
    for (int i = 1; i <= w; i++) {
        int ht;
        cin >> ht;
        if (ht > h) {
            cout << "impossible" << nl;
            return;
        }
        rem[i] = h - ht;
    }
    int lo = 0;
    int num = 0;
    for (int i = 1; i <= w; i++) {
        int nw = rem[i];
        int nxt_lo;
        int nxt_num;
        if (num) {
            int hi = lo + (num - 1) * 2;
            if (nw < hi) {
                cout << "impossible" << nl;
                return;
            }
            if (lo == 1) {
                if ((nw - hi) % 2 == 0) {
                    nxt_num = num - 1;
                    if (!nxt_num) {
                        nxt_lo = 0;
                    } else nxt_lo = 2;
                } else {
                    nxt_num = num;
                    nxt_lo = 2;
                }
            } else {
                assert(lo == 2);
                if ((nw - hi) % 2 == 0) {
                    nxt_num = num;
                    nxt_lo = 1;
                } else {
                    nxt_num = num + 1;
                    nxt_lo = 1;
                }
            }
        } else {
            if (nw & 1) {
                nxt_lo = 1;
                nxt_num = 1;
            } else {
                nxt_lo = 0;
                nxt_num = 0;
            }
        }
        swap(lo, nxt_lo);
        swap(num, nxt_num);
        // cerr << "??" << i << ' ' << nw << ' ' << lo << ' ' << num << nl;
    }
    cout << (num == 0 ? "possible" : "impossible") << nl;
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