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

mt19937 rng(time(0));

void solve() {
    int n, qq;
    cin >> n >> qq;
    vector<int> a(n);
    vector<int> b(n);
    vector<ll> rnd_val(n + 5);
    for (int i = 1; i <= n; i++) {
        rnd_val[i] = rng();
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    vector<ll> pre_a(n + 1);
    vector<ll> pre_b(n + 1);
    for (int i = 0; i < n; i++) {
        pre_a[i + 1] = pre_a[i] + rnd_val[a[i]];
    }
    for (int i = 0; i < n; i++) {
        pre_b[i + 1] = pre_b[i] + rnd_val[b[i]];
    }
    while (qq--) {
        int l, r, L, R;
        cin >> l >> r >> L >> R;
        if (r - l != R - L) {
            cout << "No" << '\n';
            continue;
        }
        cout << (pre_b[R] - pre_b[L - 1] == pre_a[r] - pre_a[l - 1] ? "Yes" : "No") << '\n';
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