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
    string s = "";
    int n = 100;
    cout << n << nl;
    for (int i = 0; i < n; i++) {
        int x = rand() % 26;
        s += (char)('a' + x);
    }
    int half = (n - 1) / 2;
    auto output = [&](int l, int r) {
        int mxl = r - l + 1;
        for (int le = 1; le <= mxl; le++) {
            for (int bg = l; bg + le - 1 <= r; bg++) {
                string tmp = "";
                for (int j = 0; j < le; j++) {
                    tmp += s[bg + j];
                }
                cout << tmp << nl;
            }
        }
        cout << nl;
    };
    output(0, half);
    output(1, half);
    output(0, n - 1);
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