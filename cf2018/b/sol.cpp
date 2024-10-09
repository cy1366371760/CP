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
    int n;
    cin >> n;
    vector<int> a(n + 5);
    vector hav(n + 5, vector<int>());
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        hav[a[i]].pb(i);
    }
    bool ifok = 1;
    set<int> ocr;
    for (int v = 1; v <= n; v++) {
        for (auto nw : hav[v]) {
            int pre = n + 1, back = -1;
            if (!ocr.empty()) {
                if ((*ocr.begin()) < nw) {
                    pre = (*ocr.begin());
                }
                if (*prev(ocr.end()) > nw) {
                    back = (*prev(ocr.end()));
                }
            }
            if (pre != n + 1) {
                if (nw - pre + 1 > v) {
                    ifok = 0;
                }
            }
            if (back != -1) {
                if (back - nw + 1 > v) {
                    ifok = 0;
                }
            }
            ocr.insert(nw);
        }
    }
    if (!ifok) {
        cout << 0 << nl;
        return;
    }
    vector<pii> segs;
    for (int i = 1; i <= n; i++) {
        segs.pb({max(1, i - a[i] + 1), min(n, i + a[i] - 1)});
    }
    int lm = -1, rm = n + 1;
    for (auto [l, r] : segs) {
        chkmax(lm, l);
        chkmin(rm, r);
    }
    // cerr << lm << ' ' << rm << nl;
    cout << max(0, rm - lm + 1) << nl;
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