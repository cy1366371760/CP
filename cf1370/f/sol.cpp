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
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    auto answer = [&](int x, int y) -> void {
        cout << "! " << x << ' ' << y << endl;
        string re;
        cin >> re;
        assert(re == "Correct");
        return;
    };
    auto ask = [&](vector<int> cur) {
        cout << "? " << cur.size() << ' ';
        for (int x : cur) cout << x << ' ';
        cout << endl;
        int x, y;
        cin >> x >> y;
        return pii(x, y);
    };
    if (n == 2) {
        answer(1, 2);
        return;
    }
    vector<int> initial;
    for (int i = 1; i <= n; i++) {
        initial.pb(i);
    }
    auto [rt, len] = ask(initial);
    vector<int> dep(n + 1, 0), father(n + 1, 0);
    vector hav(n + 5, vector<int>());
    auto dfs = [&](auto &&self, int x, int fa) -> void {
        father[x] = fa;
        for (int y : adj[x]) {
            if (y == fa) {
                continue;
            }
            dep[y] = dep[x] + 1;
            self(self, y, x);
        }
        hav[dep[x]].pb(x);
    };
    dfs(dfs, rt, 0);
    int l = (len + 1) / 2, r = min(len, *max_element(all(dep)));
    int fir = -1;
    // cerr << "GG" << ' ' << rt << endl;
    while (l <= r) {
        int mid = (l + r) >> 1;
        // cerr << "??" << l << ' ' << r << endl;
        auto [x, d] = ask(hav[mid]);
        if (d == len && adj[x].size() == 1) {
            fir = x;
            break;
        } else if (d == len) {
            fir = x;
            l = mid + 1;
        } else {
            int dt = (d - len) / 2;
            fir = x;
            for (int j = 0; j < dt; j++) {
                fir = father[fir];
            }
            r = mid - 1;
        }
    }
    int d2 = len - dep[fir];
    vector<bool> ban(n + 5, 0);
    int tmp = fir;
    while (tmp != rt) {
        ban[tmp] = 1;
        tmp = father[tmp];
    }
    vector<int> las;
    for (auto x : hav[d2]) {
        if (ban[x]) continue;
        las.pb(x);
    }
    auto [sec, _] = ask(las);
    answer(fir, sec);
}

signed main() {
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--)
        solve();
    return 0;
}