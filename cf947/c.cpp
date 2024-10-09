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
    cin >> n;
    vector<int> a(n);
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = a[i];
    }
    sort(all(b));
    int l = 0, r = n - 1, res = 0;
    auto chk = [&](int x) {
        vector<int> c(n + 5, 0);
        for (int i = 0; i < n; i++) {
            c[i + 1] = (a[i] >= b[x] ? 1 : -1);
        }
        int mn = 1e9;
        for (int i = 1; i <= n; i++) {
            c[i] += c[i - 1];
            if (c[i] - mn > 0) {
                return 1;
            }
            chkmin(mn, c[i - 1]);
        }
        return 0;
    };
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (chk(mid)) res = mid, l = mid + 1;
        else r = mid - 1;
    }
    cout << b[res] << '\n';
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
