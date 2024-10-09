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

#define BST bitset<2020>

void solve() {
    int n, m;
    cin >> n >> m;
    vector dis(n + 1, vector<int>(n + 1, 0));
    vector<BST> linked(n + 1);
    vector<BST> nlinked(n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j != i) nlinked[i][j] = 1;
        }
    }
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        dis[x][y] = max(x, y);
        linked[x][y] = 1;
        nlinked[x][y] = 0;
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            if (!dis[i][k]) continue;
            BST cur = nlinked[i] & linked[k];
            for (int j = cur._Find_first(); j <= n; j = cur._Find_next(j)) {
                dis[i][j] = max({i, j, k});
                linked[i][j] = 1;
                nlinked[i][j] = 0;
            }
        }
    }
    int qq;
    cin >> qq;
    while (qq--) {
        int x, y;
        cin >> x >> y;
        if (!dis[x][y]) dis[x][y] = -1;
        cout << dis[x][y] << nl;
    }
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