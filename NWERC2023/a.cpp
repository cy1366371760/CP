#include<bits/stdc++.h>
#define ll long long
#define int long long
#define pb push_back
#define all(x) x.begin(),x.end()
#define nl '\n'
using namespace std;

void solve() {
    int n, s;
    cin >> n >> s;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(all(a));
    if (n == 1 || s == 1) {
        cout << 1 << nl;
        return;
    }
    a.pop_back();
    a.pop_back();
    n -= 2;
    s -= 2;
    int l = 1, r = n, mid, res = 0;
    auto chk = [&](int num) {
        vector<vector<int>> cnt(3, vector<int>());
        for (int i = 0; i < num; i++) {
            cnt[a[i] % 3].pb(a[i]);
        }
        int need = 0;
        ll remain = s;
        for (auto x : cnt[0]) {
            int nw = (x + 2) / 3;
            remain -= nw;
        }
        while (!cnt[1].empty() && !cnt[2].empty()) {
            int x = cnt[1].back() + cnt[2].back();
            cnt[1].pop_back(), cnt[2].pop_back();
            remain -= (x + 2) / 3;
        }
        while (cnt[1].size()) {
            int x;
            if (cnt[1].size() >= 2) {
                x = cnt[1].back();
                cnt[1].pop_back();
                x += cnt[1].back();
                cnt[1].pop_back();
            } else {
                x = cnt[1].back();
                cnt[1].pop_back();
            }
            remain -= (x + 2) / 3;
        }
        while (cnt[2].size()) {
            int x = cnt[2].back();
            cnt[2].pop_back();
            remain -= (x + 2) / 3;
        }
        // if (num == 5) {
        //     for (int i = 0; i < num; i++) {
        //         cerr << ' ' << a[i] % 3 << ' ' << a[i] << nl;
        //     }
        //     cerr << "GG" << ' ' << remain << nl;
        // }
        return remain >= 0;
    };
    while (l <= r) {
        mid = (l + r) >> 1;
        if (chk(mid)) res = mid, l = mid + 1;
        else r = mid - 1;
    }
    cout << res + 2 << nl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
}