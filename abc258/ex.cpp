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

using Matrix = array<array<ll, 2>, 2>;

Matrix operator *(Matrix a, Matrix b) {
    Matrix res = {};
    for (int k = 0; k < 2; k++) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % mod;
            }
        }
    }
    return res;
}

Matrix qpow(Matrix x, ll y) {
    Matrix res = {{{1, 0}, {0, 1}}};
    while (y) {
        if (y & 1) res = res * x;
        x = x * x;
        y >>= 1;
    }
    return res;
}

void solve() {
    int n;
    ll s;
    cin >> n >> s;
    Matrix las;
    if (s & 1) {
        las = {{{0, 0}, {1, 0}}};
    } else {
        las = {{{0, 1}, {0, 0}}};
    }
    Matrix odd = {{{1, 0}, {1, 1}}}, even = {{{1, 1}, {0, 1}}};
    ll bf = 0;
    Matrix res = {{{1, 0}, {0, 1}}};
    auto calc = [&](ll l, ll r) {
        ll len = (r - l + 1);
        Matrix res = {{{1, 0}, {0, 1}}};
        if (len <= 0) return res;
        Matrix unit;
        if (l & 1) unit = even * odd;
        else unit = odd * even;
        res = qpow(unit, len / 2);
        if (len & 1) {
            if (l & 1) res = odd * res;
            else res = even * res;
        }
        return res;
    };
    for (int i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        res = calc(bf + 1, x - 1) * res;
        bf = x;
    }
    res = calc(bf + 1, s - 1) * res;
    res = las * res;
    cout << (res[0][0] + res[1][0]) % mod;
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