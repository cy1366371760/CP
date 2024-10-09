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
#define int long long

mt19937 rng(time(0));

void solve() {
    int k;
    cin >> k;
    int n = (1 << (k + 1));
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] ^= a[i - 1];
    }
    /*

        l, mid, r
        l ^ mid ^ r = mid
        l ^ r = 0
        l = r
    */
    map<int, pii> vis;
    auto output = [&](pii u, pii v) {
        if(u.fi > v.fi || (u.fi == v.fi && u.sc > v.sc)) {
            swap(u, v);
        }
        // u.fi <= v.fi
        if (u.fi < v.fi && v.sc < u.sc) {
            cout << u.fi << ' ' << v.fi - 1 << ' ' << v.sc + 1 << ' ' << u.sc << nl;
            return;
        } else if (u.sc < v.fi) {
            cout << u.fi << ' ' << u.sc << ' ' << v.fi << ' ' << v.sc << nl;
            return;
        } else {
            cout << u.fi << ' ' << v.fi - 1 << ' ' << u.sc + 1 << ' ' << v.sc << nl;
        }
    };
    while (1) {
        int l = rng() % n + 1;
        int r = rng() % n + 1;
        if (l > r) swap(l, r);
        int cur = a[r] ^ a[l - 1];
        if (vis.count(cur)) {
            if (vis[cur].fi != l && vis[cur].sc != r) {
                output(vis[cur], pii(l, r));
                break;
            }
        }
        vis[cur] = pii(l, r);
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