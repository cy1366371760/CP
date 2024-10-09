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
    int n;
    ll k;
    cin >> n >> k;
    vector<int> x(n);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        --x[i];
    } 
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> jp(65, vector<int>(n));
    for (int i = 0; i < n; i++) {
        jp[0][i] = x[i];
    }
    // for (int i = 0; i < n; i++) cerr << jp[0][i] << ' ';
    for (int j = 1; j <= 60; j++) {
        for (int i = 0; i < n; i++) {
            jp[j][i] = jp[j - 1][jp[j - 1][i]];
        }
    }
    for (int i = 0; i < n; i++) {
        int nw = i;
        for (int i = 60; i >= 0; i--) {
            if (k >> i & 1) {
                nw = jp[i][nw];
            }
        }
        cout << a[nw] << ' ';
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