#include<bits/stdc++.h>
#define ll long long
#define nl '\n'
using namespace std;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll r;
    cin >> r;
    ll ansx = -1, ansy = -1;
    for (ll x = 1; x <= r; x++) {
        ll y = sqrtl(r * r - x * x);
        while (x * x + y * y <= r * r) ++y;
        while (x * x + (y - 1) * (y - 1) > r * r) --y;
        y = max(y, 1LL);
        if (ansx == -1) {
            ansx = x, ansy = y;
        }
        if (x * x + y * y < ansx * ansx + ansy * ansy) {
            ansx = x;
            ansy = y;
        }
    }
    cout << ansx << ' ' << ansy << nl;
}