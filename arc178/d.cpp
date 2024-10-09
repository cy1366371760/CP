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
    const int N = 1e6 + 100;
    const ll inf = 1e18;
    const ll mod = 998244353;

    void solve() {
        int n, m;
        cin >> n >> m;
        vector<int> a(m);
        vector<int> ps(n + 5, -1);
        for (int i = 0; i < m; i++) {
            cin >> a[i];
            ps[a[i]] = i;
        }
        vector<vector<ll>> dp(m + 5, vector<ll>(m + 5, 0));
        vector<ll> f(m + 5, 0);
        bool ini = 0;
        // cerr << mn_ps << ' ' << mn_ps << '\n';
        for (int i = 0; i < n; i++) {
            vector<vector<ll>> dq(m + 5, vector<ll>(m + 5, 0));
            if (ps[i] != -1) {
                int nw = ps[i];
                if (!ini) {
                    for (int bf = 0; bf <= m; bf++) {
                        (dq[min(bf, nw)][max(bf - 1, nw)] += f[bf]) %= mod;
                    }
                    ini = 1;
                    if (i == 0) {
                        dq[nw][nw] = 1;
                    }
                }
                for (int l = 0; l < m; l++) {
                    for (int r = l; r < m; r++) {
                        (dq[min(l, nw)][max(r, nw)] += dp[l][r]) %= mod;
                    }
                }
            } else {
                if (!ini) {
                    if (i == 0) {
                        for (int j = 0; j <= m; j++) {
                            f[j] = 1;
                        }
                    } else {
                        vector<ll> g(m + 5, 0);
                        for (int bf = 0; bf <= m; bf++) {
                            for (int nw = 0; nw <= m; nw++) {
                                if (nw == bf) {
                                    g[nw] = f[nw] * 2LL % mod;
                                } else if (nw < bf) {
                                    (dq[nw][bf - 1] += f[bf]) %= mod;
                                } else {
                                    (dq[bf][nw - 1] += f[bf]) %= mod;
                                }
                            }
                        }
                        swap(f, g);
                    }
                }
                for (int r = 0; r < m; r++) {
                    ll tmp = 0;
                    for (int k = r; k >= 0; k--) {
                        (tmp += dp[k][r]) %= mod;
                        (dq[k][r] += tmp) %= mod;
                    }
                }
                for (int l = 0; l < m; l++) {
                    ll tmp = 0;
                    for (int k = l; k < m; k++) {
                        (tmp += dp[l][k]) %= mod;
                        (dq[l][k] += tmp) %= mod;
                    }
                }
            }
            swap(dp, dq);
        }
        ll ans = dp[0][m - 1];
        cout << ans << '\n';
    }

    signed main() {
        ios::sync_with_stdio(0);
        cin.tie(0);
        // int tt = 1;
        // cin >> tt;
        // while(tt--)
            solve();
        return 0;
    }
