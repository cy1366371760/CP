#include<bits/stdc++.h>
#define pb push_back
#define nl '\n'
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 5, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<bool> ok(n + 5, 1);
    int mx = -1e9;
    for (int i = 1; i <= n; i++) {
        if (a[i] < mx) ok[i] = 0;
        mx = max(mx, a[i]);
    }
    int mn = 1e9;
    for (int i = n; i >= 1; i--) {
        if (a[i] > mn) ok[i] = 0;
        mn = min(mn, a[i]);
    }
    vector<int> res;
    for (int i = 1; i <= n; i++) {
        if (ok[i]) res.pb(a[i]);
    }
    cout << res.size() << ' ';
    int sz = min(100, (int)res.size());
    for (int i = 0; i < sz; i++) {
        cout << res[i] << ' ';
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}