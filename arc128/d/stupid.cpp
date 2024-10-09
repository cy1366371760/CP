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
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    map<vector<int>, bool> vis;
    auto dfs = [&](auto &&self, vector<int> sta) {
        if (vis.count(sta)) return;
        vis[sta] = 1;
        for (int i = 1; i + 1 < sta.size(); i++) {
            if (sta[i] != sta[i - 1] && sta[i] != sta[i + 1]) {
                auto nsta = sta;
                nsta.erase(nsta.begin() + i);
                self(self, nsta);
            }
        }
    };
    dfs(dfs, a);
    cout << vis.size() << '\n';
    for (auto [sta, _] : vis) {
        for (auto x : sta) cerr << x << ' ';
        cerr << '\n';
    }
    /*
    2 4 1
    3 2 2
    4 2 2
    5 9 2
    6 6 4
    7 9 8
    8 6 16
    9 6 16
*/
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