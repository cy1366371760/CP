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
    int n, m;
    cin >> n >> m;
    vector<int> keep1, keep2;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        if (x < y) keep1.pb(i);
        else keep2.pb(i);
    }
    if (keep1.size() < keep2.size()) keep1 = keep2;
    cout << "YES" << '\n';
    cout << keep1.size() << '\n';
    for (int i = 0; i < keep1.size(); i++) {
        cout << keep1[i] << " \n"[i == keep1.size() - 1];
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