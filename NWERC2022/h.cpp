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

void solve() {
    int n;
    cin >> n;
    vector adj(n + 5, vector<int>());
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    vector<int> dep(n + 5, 0);
    vector<int> mnd(n + 5, 0);
    vector<int> mxd(n + 5, 0);
    vector<int> in(n + 5, 0);
    vector<int> ot(n + 5, 0);
    vector<int> dfn_lst;
    dfn_lst.pb(0);
    vector<vector<pii>> laz(n + 5);
    int tim = 0;
    auto dfs = [&](auto &&self, int x, int fa) -> void {
        in[x] = ++tim;
        dfn_lst.pb(x);
        vector<pii> son;
        for (int y : adj[x]) {
            if (y == fa) continue;
            dep[y] = dep[x] + 1;
            self(self, y, x);
            son.pb(pii(y, mxd[y]));
        }
        ot[x] = tim;
        if (son.size() <= 1) {
            mnd[x] = dep[x];
        } else {
            mnd[x] = (int)1e9;
            for (auto [y, d] : son) {
                mnd[x] = min(mnd[x], d);
            }
        }
        mxd[x] = mnd[x];
        for (auto [y, d]: son) {
            if (d >= mnd[x] + 1) {
                mxd[x] = mnd[x] + 1;
            }
            if (d > mnd[x] + 1) {
                laz[in[y]].pb({mnd[x] + 2, 1});
                laz[ot[y] + 1].pb({mnd[x] + 2, -1});
            }
        }
    };
    dfs(dfs, 1, 0);
    multiset<int> st;
    int res = 0;
    for (int i = 1; i <= tim; i++) {
        for (auto [d, tp] : laz[i]) {
            if (tp == 1) st.insert(d);
            else st.extract(d);
        }
        int d = dep[dfn_lst[i]];
        if (!st.empty() && (*st.begin()) <= d) {
            ++res;
        }
    }
    cout << res << nl;
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