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
const int N = 888;
const ll inf = 1e18;
const ll mod = 998244353;

bool dp[N][N], dq[N][N];

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 5);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    memset(dp, 0, sizeof dp);
    memset(dq, 0, sizeof dq);
    dp[0][0] = 1;
    auto isok = [&](int ps, int val, int del) {
        if (ps == n) return 0;
        if (ps < val) return 0;
        int need = ps - val;
        if (need < 0) return 0;
        if (need & 1) return 0;
        need /= 2;
        if (need > del) return 0;
        return 1;
    };
    for (int i = 1; i <= n; i++) {
        // vector<vector<bool>> dq(2, vector<bool>(n + 5, 0));
        memset(dq, 0, sizeof dq);
        for (int del = 0; del <= i / 2 + 1; del++) {
            for (int left = 0; left < i; left++) {
                // cerr << "??" << i << ' ' << del << ' ' << left << ' ' << dp[del][left] << '\n';
                if (dp[del][left]) {
                    cerr << "fafa" << i - 1 << ' ' << del << ' ' << left << '\n';
                    // if (i == 2 && del == 0 && left == 1) {
                    //     cerr << "!!" << i << ' ' << a[i] << ' ' << del << ' ' << left << '\n';
                    //     cerr << isok(i, a[i], del) << '\n';
                    // }
                    if (isok(i, a[i], del)) {
                        dq[del][left + 1] = 1;
                    }
                    if (left > 0) {
                        dq[del + 1][left - 1] = 1;
                        if (del + 1 == 2 && i == 4) {
                            cerr << "??" << i - 1 << ' ' << del << ' ' << left << ' ' << dp[del][left] << '\n';
                        }
                    } else {
                        dq[del][left] = 1;
                    }
                }
            }
        }
        memcpy(dp, dq, sizeof dq);
    }
    int ans = 0;
    for (int del = 1; del <= n / 2; del++) {
        if (dp[del][0]) {
            ans = del;
        }
    }
    cout << ans << '\n';
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
