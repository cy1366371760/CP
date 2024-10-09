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
    vector adj(n + 1, vector<int>());
    vector<int> father(n + 1, 0);
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    vector<int> dep(n + 1, 0);
    auto dfs = [&](auto &&self, int x, int fa) -> void {
        father[x] = fa;
        for (int y : adj[x]) {
            if (y == fa) continue;
            dep[y] = dep[x] + 1;
            self(self, y, x);
        }
    };
    dep[1] = 1;
    dfs(dfs, 1, 0);
    set<pii> ban;
    int rem = n;
    vector<int> sz(n + 1, 0);
    auto find_rt = [&](int x) {
        int all_sz = rem, rt = -1, best_sz = (int)1e9;
        auto dfs = [&](auto &&self, int x, int fa) -> void {
            sz[x] = 1;
            int big = 0;
            for (int y : adj[x]) {
                if (ban.count(pii(x, y))) continue;
                if (y == fa) continue;
                self(self, y, x);
                chkmax(big, sz[y]);
                sz[x] += sz[y];
            }
            chkmax(big, all_sz - sz[x]);
            if (big < best_sz) {
                best_sz = big;
                rt = x;
            }
        };
        dfs(dfs, x, 0);
        return rt;
    };
    auto ask = [&](string type, int x) {
        cout << type << ' ' << x << endl;
        int re;
        if (type != "!") {
            cin >> re;
        }
        return re;
    };
    int dx = ask("d", 1) + 1;
    int rt = 1, rem_rt = 1;
    while (1) {
        rt = find_rt(rem_rt);
        int dis = ask("d", rt);
        if (dis == 0) {
            ask("!", rt);
            break;
        }
        bool above = (dep[rt] > dx);
        above |= (dx - dep[rt] != dis);
        if (above) {
            ban.insert({rt, father[rt]});
            ban.insert({father[rt], rt});
            rem = rem - sz[rt];
        } else {
            int nxt = ask("s", rt);
            ban.insert({rt, nxt});
            ban.insert({nxt, rt});
            rem = sz[nxt];
            rem_rt = nxt;
        }
    }
}

signed main() {
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    // int tt = 1;
    // cin >> tt;
    // while(tt--)
        solve();
    return 0;
}
