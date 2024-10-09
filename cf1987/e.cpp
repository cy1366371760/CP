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
const int N = 5050;
const ll inf = 1e18;
const ll mod = 998244353;

int n, p[N], dep[N];
ll a[N], tot_cost;
vector<int> adj[N];
vector<pll> val[N];

vector<pll> mg(vector<pll> &a, vector<pll> &b) {
    vector<pll> res;
    for (int i = 0, j = 0; i < a.size() || j < b.size(); ) {
        if (i == a.size()) {
            res.pb(b[j++]);
            continue;
        }
        if (j == b.size()) {
            res.pb(a[i++]);
            continue;
        }
        if (a[i].fi < b[j].fi) {
            res.pb(a[i++]);
        } else {
            res.pb(b[j++]);
        }
    }
    return res;
}

void dfs(int x) {
    auto &cur = val[x];
    ll sum = 0;
    for (int y : adj[x]) {
        dep[y] = dep[x] + 1, dfs(y);
        cur = mg(cur, val[y]);
        sum += a[y];
    }
    if (sum < a[x]) {
        ll las = a[x] - sum;
        for (int i = 0; i < cur.size(); i++) {
            ll use = min(las, cur[i].sc);
            las -= use;
            cur[i].sc -= use;
            tot_cost += use * (cur[i].fi - dep[x]);
        }
        vector<pll> rem;
        for (auto [d, c] : cur) {
            if (c > 0)
                rem.eb(d, c);
        }
        cur = rem;
    } else if (sum > a[x]) {
        vector<pll> fafa;
        fafa.eb(dep[x], sum - a[x]);
        cur = mg(cur, fafa);
    }
    if (adj[x].empty())
        cur.eb(dep[x], 1e18);
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        adj[i].clear(), val[i].clear();
    for (int i = 2; i <= n; i++) {
        cin >> p[i];
        adj[p[i]].pb(i);
    }
    tot_cost = 0;
    dep[1] = 0, dfs(1);
    cout << tot_cost << '\n';
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
