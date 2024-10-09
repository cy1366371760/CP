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
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] = (a[i] + a[i - 1]) % 10;
    }
    vector<int> nxt(11, -1);
    vector<int> res;
    for (int i = n; i >= 1; i--) {
        nxt[a[i]] = i;
        int cur = nxt[a[i - 1]];
        if (cur != -1) cur = cur - i + 1;
        res.pb(cur);
    }
    reverse(all(res));
    for (int x : res) cout << x << ' ';
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