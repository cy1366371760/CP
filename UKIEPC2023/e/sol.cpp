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
    string s;
    cin >> s;
    int n = s.length();
    vector<vector<int>> val(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            cin >> val[i][j];
            val[j][i] = val[i][j];
        }
    }
    vector<int> lhs, rhs;
    for (int i = 0; i < n / 2; i++) lhs.pb(i);
    for (int i = n / 2 + 1; i < n; i++) rhs.pb(i);
    int lim = (1 << rhs.size()) - 1;
    for (int i = 0; i <= lim; i++) {

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
