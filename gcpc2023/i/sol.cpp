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
    const int m = N * 2 - 10;
    vector<int> ps(n + 1, 0);
    vector<bool> vis(N * 2, 0);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        ps[i] = x;
        vis[x] = 1;
    }
    set<int> unplace;
    for (int i = 1; i <= m; i++) {
        if (!vis[i]) unplace.insert(i);
    }
    int qq;
    cin >> qq;
    while (qq--) {
        int i;
        cin >> i;
        int nw = ps[i];
        auto nx = (*unplace.lower_bound(nw));
        cout << nx << nl;
        ps[i] = nx;
        unplace.erase(nx);
        unplace.insert(nw);
    }
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