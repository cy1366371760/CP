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
    vector<ll> a(n + 5);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    ll mx_val = a[1];
    ll need = 0;
    ll sum = a[1];
    for (int i = 2; i <= n; i++) {
        sum += a[i];
        if (a[i] < mx_val) {
            need += mx_val - a[i];
        } else {
            ll giv = min(need, a[i] - mx_val);
            a[i] -= giv;
            need -= giv;
            if (a[i] > mx_val) {
                mx_val = sum / i;
                if (sum % i) mx_val++;
            }
        }
    }
    if (need) {
        cout << "No" << nl;
        return;
    }
    cout << "Yes" << nl;
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