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

map<vector<int>, bool> vis;

int ans;

void dfs(vector<int> cur) {
    if (vis.count(cur)) return;
    vis[cur] = 1;
    ans = min(ans, (int)cur.size());
    int n = cur.size();
    for (int i = 0; i < n; i++) {
        if (cur[i] == i && i + 1 < n) {
            vector<int> nxt;
            for (int j = 0; j < i; j++)
                nxt.pb(cur[j]);
            for (int j = i + 2; j < n; j++)
                nxt.pb(cur[j]);
            dfs(nxt);
        }
    }
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i], --a[i];
    vis.clear();
    ans = 1e5;
    dfs(a);
    cout << (n - ans) / 2 << '\n';
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
