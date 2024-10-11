#include<bits/stdc++.h>
#define ll long long
#define nl '\n'
#define pb push_back
#define all(x) (x).begin(),(x).end()
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<ll> a;
    ll mx = -1e18;
    for (int i = 0; i < n; i++) {
        string s;
        ll val;
        cin >> s >> val;
        if (s == "pig") mx = max(mx, val);
        else a.pb(val);
    }
    sort(all(a));
    ll ans = mx;
    for (auto v : a) {
        if (v < mx) {
            ans += v;
        }
    }
    cout << ans << nl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}