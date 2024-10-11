#include<bits/stdc++.h>
#define ll long long
#define nl '\n'
#define pb push_back
#define all(x) (x).begin(),(x).end()
using namespace std;
const int N = 5e5 + 100;

int fen[N];

void solve() {
    int n;
    cin >> n;
    vector<int> fir(n + 5, 0), sec(n + 5, 0), a(n + 5, 0);
    for (int i = 1; i <= n; i++) {
        cin >> fir[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> sec[i];
        a[fir[i]] = sec[i];
    }
    auto add = [&](int x, int y) {
        for (; x <= n; x += x & -x) fen[x] += y;
    };
    auto ask = [&](int x) {
        ll res = 0;
        for (; x; x -= x & -x) res += fen[x];
        return res;  
    };
    auto calc_inv = [&](vector<int> &cur) {
        ll res = 0;
        for (int i = 1; i <= n; i++) {
            res += (i - 1) - ask(cur[i]);
            add(cur[i], 1);
        }
        for (int i = 1; i <= n; i++) {
            add(cur[i], -1);
        }
        return res;
    };
    if (calc_inv(a) & 1) {
        cout << "No" << nl;
        return;
    }
    int l = 1, r = n - 1, mid, res = n;
    while (l <= r) {
        mid = (l + r) >> 1;
        ll up_inv = 1LL * (n - mid) * (n - mid + 1) / 2;
        vector<int> cur;
        cur.pb(0);
        for (int i = 1; i < mid; i++) {
            cur.pb(a[i]);
        }
        for (int i = n; i >= mid; i--) {
            cur.pb(a[i]);
        }
        ll down_inv = calc_inv(cur);
        if (down_inv >= up_inv) {
            res = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    vector<int> up, down;
    up.pb(0), down.pb(0);
    for (int i = 1; i < res; i++) {
        up.pb(i);
        down.pb(a[i]);
    }
    for (int i = n; i >= res; i--) {
        up.pb(i);
        down.pb(a[i]);
    }
    // cerr << "??" << res << nl;
    // for (int i = 1; i <= n; i++) {
    //     cerr << up[i] << ' ';
    // } cerr << nl;
    //  for (int i = 1; i <= n; i++) {
    //     cerr << down[i] << ' ';
    // } cerr << nl;
    int bound = res;
    if (bound > 1)
    {
        int l = bound, r = n, mid, res = bound - 1;
        while (l <= r) {
            mid = (l + r) >> 1;
            vector<int> nup, ndown;
            nup.pb(0), ndown.pb(0);
            for (int i = 1; i < bound - 1; i++) {
                nup.pb(up[i]);
                ndown.pb(down[i]);
            }
            for (int i = bound; i <= n; i++) {
                nup.pb(up[i]);
                ndown.pb(down[i]);
                if (i == mid) nup.pb(up[bound - 1]), ndown.pb(down[bound - 1]);
            }
            if (calc_inv(nup) <= calc_inv(ndown)) {
                res = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        vector<int> nup, ndown;
        nup.pb(0);
        ndown.pb(0);
        // cerr << "!!" << res << nl;
        for (int i = 1; i < bound - 1; i++) {
            nup.pb(up[i]);
            ndown.pb(down[i]);
        }
        if (res == bound - 1) nup.pb(up[bound - 1]), ndown.pb(down[bound - 1]);
        for (int i = bound; i <= n; i++) {
            nup.pb(up[i]);
            ndown.pb(down[i]);
            if (i == res) nup.pb(up[bound - 1]), ndown.pb(down[bound - 1]);
        }
        swap(up, nup);
        swap(down, ndown);
    }
    cout << "Yes" << nl;
    for (int i = 1; i <= n; i++) cout << up[i] << ' '; cout << nl;
    for (int i = 1; i <= n; i++) cout << down[i] << ' '; cout << nl;
    // cerr << "FFFF" << ' ' << calc_inv(up) << ' ' << calc_inv(down) << nl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}