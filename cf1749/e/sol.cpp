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
const int inf = 1e9;
const ll mod = 998244353;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1 ,1};

const int dx2[] = {-1, -1, 1, 1};
const int dy2[] = {-1, 1, -1, 1};

int cas = 0;

void solve() {
    ++cas;
    int n, m;
    cin >> n >> m;
    vector a(n + 5, vector<int> (m + 5, 0));
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for (int j = 1; j <= m; j++) {
            if (s[j - 1] == '#') {
                a[i][j] = 1;
            }
        }
    }
    vector prev(n + 5, vector<pii> (m + 5, pii(-1, -1)));
    vector dis(n + 5, vector<int>(m + 5, -1));
    vector ban(n + 5, vector<bool>(m + 5, 0));
    deque<pii> que;
    for (int row = 0; row <= n + 1; row++) {
        dis[row][0] = 0;
        que.pb({row, 0});
    } 
    for (int row = 1; row <= n; row++) {
        for (int col = 1; col <= m; col++) {
            for (int d = 0; d < 4; d++) {
                int nrow = row + dx[d];
                int ncol = col + dy[d];
                if (a[nrow][ncol]) ban[row][col] = 1;
            }
        }
    }
    while (!que.empty()) {
        auto [row, col] = que.front();
        que.pop_front();
        for (int d = 0; d < 4; d++) {
            int nrow = row + dx2[d];
            int ncol = col + dy2[d];
            if (nrow >= 1 && nrow <= n && ncol >= 1 && ncol <= m) {
                if (!ban[nrow][ncol] && dis[nrow][ncol] == -1) {
                    dis[nrow][ncol] = dis[row][col] + (a[nrow][ncol] == 0);
                    prev[nrow][ncol] = pii(row, col);
                    if (a[nrow][ncol] == 0) que.pb({nrow, ncol});
                    else que.push_front({nrow, ncol});
                }
            }
        }
    }
    int mn_ps = 1;
    for (int i = 2; i <= n; i++) {
        if (dis[i][m] == -1) continue;
        if (dis[mn_ps][m] == -1 || dis[i][m] < dis[mn_ps][m]) {
            mn_ps = i;
        }
    }
    if (dis[mn_ps][m] == -1) {
        cout << "NO" << nl;
        return;
    }
    cout << "YES" << nl;
    int row = mn_ps, col = m;
    do {
        a[row][col] = 1;
        tie(row, col) = prev[row][col];
    } while (row != -1 && col != -1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << (a[i][j] == 0 ? '.' : '#');
        }
        cout << nl;
    }
    // cerr << "!! cost: " << dis[mn_ps][m] << nl;
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