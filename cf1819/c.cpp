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
        // x = i, y = i + 1;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    if (n == 2) {
        cout << "Yes" << nl;
        cout << 1 << ' ' << 2 << nl;
        return;
    }
    int rt = -1;
    for (int i = 1; i <= n; i++) {
        if (adj[i].size() >= 2) {
            rt = i;
            break;
        }
    }
    // 0 start at x, ed at a son
    // 1 start at a son, ed at x
    auto get_ans = [&](auto &&self, int x, int fa, int type, deque<int> &res) -> void {
        // cerr << "!!" << x << ' ' << fa << ' ' << type << nl;
        vector<int> big;
        for (int y : adj[x]) {
            if (y == fa) continue;
            if (adj[y].size() > 1) {
                big.pb(y);
            }
        }
        if (big.size() > 1) {
            cout << "No" << nl;
            exit(0);
        }
        if (big.size()) {
            self(self, big[0], x, type ^ 1, res);
        }
        {
            for (int y : adj[x]) {
                if (y == fa) continue;
                if (adj[y].size() > 1) {
                    continue;
                }
                
                if (type == 0) res.pb(y);
                else res.push_front(y);
            }
        }
        if (type == 0) res.push_front(x);
        if (type == 1) res.pb(x);
    };
    deque<int> res, res2;
    vector<int> big;
    for (int son : adj[rt]) {
        if (adj[son].size() > 1) {
            big.pb(son);
        }
    }
    if (big.size() > 2) {
        cout << "No" << nl;
        return;
    }
    if (big.size() >= 1) {
        get_ans(get_ans, big[0], rt, 1, res);
    }
    for (int son : adj[rt]) {
        if (adj[son].size() == 1) {
            res.pb(son);
        }
    }
    res.push_front(rt);
    if (big.size() == 2) {
        get_ans(get_ans, big[1], rt, 0, res2);
    }
    res.insert(res.end(), all(res2));
    cout << "Yes" << nl;
    for (int x : res) cout << x << ' ';
    cout << nl;
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