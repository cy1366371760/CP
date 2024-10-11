#include<bits/stdc++.h>
#define ll long long
#define pll pair<ll, ll>
#define nl '\n'
#define pb push_back
#define all(x) (x).begin(),(x).end()
using namespace std;
const ll mod = 1e10;

void solve() {
    ll a = 0, b = 1;
    map<pll, int> vis;
    vis[pll(a, b)] = 0;
    for (int i = 2; ; i++) {
        ll c = (a + b) % mod;
        pll nw = pll(b, c);
        if (vis.count(nw)) {
            cerr << vis[nw] << ' ' << i << nl;
            return;
        }
        vis[nw] = i;
        a = b;
        b = c;
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}