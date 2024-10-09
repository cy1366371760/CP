#include<bits/stdc++.h>
#define ll long long
#define nl '\n'
using namespace std;
const ll inf = 1e18;

void solve() {
    int n;
    cin >> n;
    vector<ll> h(n + 5, inf);
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }
    vector<int> go_l(n + 5, 0);
    vector<int> go_r(n + 5, n + 1);
    for (int i = n; i >= 1; i--) {
        if (h[i + 1] > h[i]) go_r[i] = i + 1;
        else go_r[i] = go_r[i + 1];
    }
    for (int i = 1; i <= n; i++) {
        if (h[i - 1] > h[i]) go_l[i] = i - 1;
        else go_l[i] = go_l[i - 1];
    }
    ll ans = -1;
    for (int i = 1; i <= n; i++) {
        int ps_l = go_l[i] + 1;
        int ps_r = go_r[i] - 1;
        ans = max(ans, min(h[i] - h[ps_l], h[i] - h[ps_r]));
    }
    cout << ans << nl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
}