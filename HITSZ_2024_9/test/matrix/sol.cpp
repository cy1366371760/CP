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
    int n, m;
    cin >> n >> m;
    vector a(n + 5, vector<int> (m + 5, 0));
    auto vis = a;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }   
    }
    int vis_num = 0;
    while (1) {
        int si = -1, sj = -1;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (vis[i][j]) continue;
                si = i, sj = j;
                break;
            }
            if (si != -1 && sj != -1) break;
        }
        if (a[si][sj] == 0) {
            cout << "NO" << nl;
            return;
        }
        int len = 1;
        while (sj + len <= m && !vis[si][sj + len] && a[si][sj + len] == 0) ++len;
        for (int row = si; row < si + len; row++) {
            if(row > n) {
                cout << "NO" << nl;
                return;
            }
            for (int col = sj; col < sj + len; col++) {
                if (vis[row][col]) {
                    cout << "NO" << nl;
                    return;
                }
                vis[row][col] = 1;
                ++vis_num;
                if (col - sj == row - si) {
                    if (a[row][col] != 1) {
                        cout << "NO" << nl;
                        return;
                    }
                } else {
                    if (a[row][col] != 0) {
                        cout << "NO" << nl;
                        return;
                    }
                }
            }
        }
        if (vis_num == n * m) {
            cout << "YES" << nl;
            return;
        }
    }
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