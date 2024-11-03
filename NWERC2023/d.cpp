#include<bits/stdc++.h>
#define ll long long
#define int long long
#define pb push_back
#define all(x) x.begin(),x.end()
#define nl '\n'
using namespace std;
using ld = long double;

void solve() {
    vector a(7, vector<int>(24, 0));
    for (int i = 0; i < 7; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < 24; j++) {
            a[i][j] = (s[j] == '.');
        }
    }
    int d, h;
    cin >> d >> h;
    ld ans = 0;
    for (int s = 0; s < (1 << 7); s++) {
        if (__builtin_popcount(s) != d) continue;
        vector<int> val(24, 0);
        for (int j = 0; j < 7; j++) {
            if (~s >> j & 1) continue;
            for (int k = 0; k < 24; k++) {
                val[k] += a[j][k];
            }
        }
        sort(all(val));
        reverse(all(val));
        int ok = 0;
        for (int j = 0; j < h; j++) {
            ok += val[j];
        }
        ans = max(ans, (ld)1.0 * ok / (d * h));
    }
    cout << fixed << setprecision(10) << ans << nl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
}