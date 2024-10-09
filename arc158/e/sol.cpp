#include<bits/stdc++.h>

#define nl '\n'
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

void Add(ll &x, ll y) {
    x = (x + y) % mod;
}
void Sub(ll &x, ll y) {
    x = (x - y + mod) % mod;
}

void solve() {
    ll n;    
    cin >> n;
    vector a(2, vector<ll>(n + 5, 0LL));
    vector sum(2, vector<ll>(n + 5, 0LL));
    vector ssum(2, vector<ll>(n + 5, 0LL));
    vector sam_key(2, vector<ll>(n + 5, 0LL));
    vector dif_key(2, vector<ll>(n + 5, 0LL));
    for (int nw = 0; nw < 2; nw++) {
        for (int i = 1; i <= n; i++) {
            cin >> a[nw][i];
            sum[nw][i] = sum[nw][i - 1] + a[nw][i];
        }
    }
    for (int nw = 0; nw < 2; nw++) {
        for (int i = 1; i <= n; i++) {
            ssum[nw][i] = sum[nw][i] % mod;
            Add(ssum[nw][i], ssum[nw][i - 1]);
        }
    }
    for (int nw = 0; nw < 2; nw++) {
        int nxt = 1 ^ nw;
        for (int i = 1; i <= n; i++) {
            sam_key[nw][i] = sum[nw][i - 1] - sum[nxt][i];
            dif_key[nw][i] = sum[nxt][i - 1] - sum[nw][i];
        }
    }
    auto ask_sum = [&](int row, int l, int r) {
        return (sum[row][r] % mod - sum[row][l - 1] % mod + mod) % mod;
    };
    auto ask_ssum = [&](int row, int l, int r) {
        return (ssum[row][r] - ssum[row][l - 1] + mod) % mod;
    };
    vector sam_que(2, deque<pll>());
    vector dif_que(2, deque<pll>());
    vector dp(2, vector(2, vector<ll> (n + 5, 0LL)));
    vector go(2, vector<int>(2, n + 1));
    vector mx_save(2, vector<ll> (2, -inf));
    vector las_upd(2, vector<int>(2, n + 1));
    ll ans = 0;
    for (int i = n; i >= 1; i--) {
        ll bf = ans;
        for (int nw = 0; nw < 2; nw++) {
            int nxt = 1 ^ nw;
            // same row
            // {
            //     ll &cur = dp[nw][nw][i];
            //     ll tmp = sum[nw][i] - sum[nxt][i - 1];
            //     int j = lower_bound(all(sam_que[nw]), pll(tmp, -1)) - sam_que[nw].begin();
            //     if (j < sam_que[nw].size()) j = sam_que[nw][j].sc;
            //     else j = n + 1;
            //     chkmin(go[nw][nw], j);
            //     j = go[nw][nw];
            //     if (i == 1 && nw == 0) {
            //         cerr << "fuck?" << ' ' << tmp << ' ' << j << nl;
            //     }
            //     Add(cur, ask_ssum(nw, i, j - 1));
            //     Sub(cur, sum[nw][i - 1] * (j - i) % mod);
            //     Add(cur, dp[nxt][nw][j]);
            //     tmp = (a[nw][i] + ask_sum(nxt, i, j - 1)) % mod;
            //     Add(cur, tmp * (n + 1 - j) % mod);
            //     Add(ans, cur);
            // }
            // dif 
            {
                ll &cur = dp[nw][nxt][i];
                ll tmp = sum[nxt][i - 1] - sum[nw][i];
                ll cur_save = -inf;
                int j = lower_bound(all(dif_que[nw]), pll(tmp, -1)) - dif_que[nw].begin();
                if (j < dif_que[nw].size()) {
                    cur_save = dif_que[nw][j].fi - tmp;
                    j = dif_que[nw][j].sc;
                } else j = n + 1;
                // if (i == 1 && nw == 0) {
                //     cerr << "shit" << j << ' ' << go[nxt][nxt] << nl;
                // }
                if (go[nxt][nxt] < j || (j == go[nxt][nxt] && cur_save < mx_save[nxt][nxt])) {
                    // cerr << "miao? " << i << ' ' << nw << ' ' << j << ' ' << go[nxt][nxt] << ' ' << las_upd[nxt][nxt] << nl;
                    j = go[nxt][nxt];
                    Add(cur, ask_ssum(nxt, i, j - 1));
                    Sub(cur, sum[nxt][i - 1] % mod * (j - i) % mod);
                    Add(cur, a[nw][i] * (j - i));
                    Add(cur, dp[nw][nxt][j]);
                    int k = las_upd[nxt][nxt];
                    tmp = (a[nw][i] + ask_sum(nxt, i, k)) % mod;
                    Add(tmp, ask_sum(nw, k, j - 1));
                    Add(cur, tmp * (n + 1 - j) % mod);
                    Add(ans, cur);
                } else {
                    Add(cur, ask_ssum(nxt, i, j - 1));
                    Sub(cur, sum[nxt][i - 1] % mod * (j - i) % mod);
                    Add(cur, a[nw][i] * (j - i));
                    Add(cur, dp[nw][nxt][j]);
                    tmp = ask_sum(nw, i, j - 1);
                    Add(cur, tmp * (n + 1 - j) % mod);
                    Add(ans, cur);
                }
            }
        }
        for (int nw = 0; nw < 2; nw++) {
            int nxt = 1 ^ nw;
            // same row
            {
                ll &cur = dp[nw][nw][i];
                ll tmp = sum[nw][i] - sum[nxt][i - 1];
                ll cur_save = -inf;
                int j = lower_bound(all(sam_que[nw]), pll(tmp, -1)) - sam_que[nw].begin();
                if (j < sam_que[nw].size()) {
                    cur_save = sam_que[nw][j].fi - tmp;
                    j = sam_que[nw][j].sc;
                }
                else j = n + 1;
                if (j < go[nw][nw] || (j == go[nw][nw] && cur_save > mx_save[nw][nw])) {
                    go[nw][nw] = j;
                    mx_save[nw][nw] = cur_save;
                    las_upd[nw][nw] = i;
                } else {
                    j = go[nw][nw];
                }
                int k = las_upd[nw][nw];
                Add(cur, ask_ssum(nw, i, j - 1));
                Sub(cur, sum[nw][i - 1] % mod * (j - i) % mod);
                Add(cur, dp[nxt][nw][j]);
                tmp = (ask_sum(nw, i, k) + ask_sum(nxt, k, j - 1)) % mod;
                Add(cur, tmp * (n + 1 - j) % mod);
                Add(ans, cur);
            }
            // dif 
            // {
            //     ll &cur = dp[nw][nxt][i];
            //     ll tmp = sum[nxt][i - 1] - sum[nw][i];
            //     int j = lower_bound(all(dif_que[nw]), pll(tmp, -1)) - dif_que[nw].begin();
            //     if (j < dif_que[nw].size()) j = dif_que[nw][j].sc;
            //     else j = n + 1;
            //     if (i == 1) cerr << "fafa" << nw << ' ' << j << nl;
            //     Add(cur, ask_ssum(nxt, i, j - 1));
            //     Sub(cur, sum[nxt][i - 1] * (j - i) % mod);
            //     Add(cur, a[nw][i] * (j - i));
            //     Add(cur, dp[nw][nxt][j]);
            //     tmp = ask_sum(nw, i, j - 1);
            //     Add(cur, tmp * (n + 1 - j) % mod);
            //     Add(ans, cur);
            // }
        }
        // if (i == 1) {
        //     for (int fr = 0; fr < 2; fr++) {
        //         for(int to = 0; to < 2; to++) {
        //             cerr << "fr: " << fr << ' ' << "to: " << to << ' ' << dp[fr][to][i] << nl;
        //         }
        //     }
        // }
        for (int nw = 0; nw < 2; nw++) {
            auto &que = sam_que[nw];
            pll val = pll(sam_key[nw][i], i);
            while (!que.empty() && que.front().fi <= val.fi) que.pop_front();
            que.push_front(val);
        }
        for (int nw = 0; nw < 2; nw++) {
            auto &que = dif_que[nw];
            pll val = pll(dif_key[nw][i], i);
            while (!que.empty() && que.front().fi <= val.fi) que.pop_front();
            que.push_front(val);
        }
        // cerr << "!!" << i << ' ' << ans - bf << nl;
    }
    ll extra = ans;
    for (int i = 1; i <= n; i++) {
        Sub(extra, (3LL * a[0][i] + 3LL * a[1][i]) % mod);
    }
    Add(ans, extra);
    cout << ans << nl;
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