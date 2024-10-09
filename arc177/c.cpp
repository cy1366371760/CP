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

const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++) {
            a[i][j] = (s[j] == 'R' ? 0 : 1);
        }
    }
    auto ask = [&]() {
        vector<vector<int>> dis(n, vector<int>(n, 1e9));
        vector<vector<bool>> vis(n, vector<bool>(n, 0));
        dis[0][0] = 0;
        deque<pii> que;
        que.push_back(pii(0, 0));
        while (!que.empty()) {
            auto [x, y] = que.front();
            que.pop_front();
            if (vis[x][y]) {
                continue;
            }
            vis[x][y] = 1;
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n) {
                    continue;
                }
                if (dis[nx][ny] > dis[x][y] + a[nx][ny]) {
                    dis[nx][ny] = dis[x][y] + a[nx][ny];
                    if (a[nx][ny] == 0) {
                        que.push_front(pii(nx, ny));
                    } else {
                        que.push_back(pii(nx, ny));
                    }
                }
            }
        }
        return dis[n - 1][n - 1];
    };
    int ans = ask();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] ^= 1;
        }
        reverse(all(a[i]));
    }
    ans += ask();
    cout << ans << '\n';
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
