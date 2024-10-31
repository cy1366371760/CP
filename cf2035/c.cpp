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
    deque<int> res;
    bool odd = 0;
    if (n & 1) odd = 1, --n;
    if (n == 4) {
        res = deque<int>{2, 1, 3, 4};
    } else if (n == 6) {
        res = deque<int>{1, 2, 4, 6, 5, 3};
    } else {
        int v = 8;
        res = deque<int>{2, 4, 5, 1, 3, 6, 7, 8};
        while (v * 2 <= n) {
            int sz = res.size();
            for (int i = 0; i < sz; i++) {
                res.pb(res[i] + v);
            }
            v *= 2;
        }
        for (int i = v + 1; i <= n; i++) {
            res.push_front(i);
        }
    }
    if (odd) {
        res.pb(n + 1);
    }
    int ans = 0;
    for (int i = 0; i < res.size(); i++) {
        if (i & 1) ans |= res[i];
        else ans &= res[i];
    }
    cout << ans << nl;
    for (int x : res) cout << x << ' ';
    cout << nl;
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