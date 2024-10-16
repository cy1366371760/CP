#include<bits/stdc++.h>
#define nl '\n'
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 5), b(m + 5, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.begin() + n + 1);
    if (n <= m) cout << a[n] << nl;
    else {
        for (int i = 1; i <= m; i++) {
            b[i] += a[n - i + 1];
        }
        for (int i = n - m, j = m; i >= 1; i--, j--) {
            b[j] += a[i];
        }
        cout << *max_element(b.begin(), b.end()) << nl;
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}