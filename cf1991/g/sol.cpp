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
    int n, m, k, q;
    cin >> n >> m >> k >> q;
    string s;
    cin >> s;
    vector<vector<int>> sta(n + 5, vector<int>(m + 5, 0));
    bool rev = 0;
    auto doit = [&](int row, int col, int type) {
        // cerr << "!!" << row << ' ' << col << ' ' << type << '\n';
        if (type == 1) cout << row - k + 1 << ' ' << col << '\n';
        else cout << row << ' ' << col << '\n';
        if (type == 0) {
            for (int j = col; j < col + k; j++) {
                assert(sta[row][j] == 0);
                sta[row][j] = 1;
            }
        } else {
            for (int i = row; i > row - k; i--) {
                assert(sta[i][col] == 0);
                sta[i][col] = 2;
            }
        }
        auto nsta = sta;
        for (int i = 1; i <= n; i++) {
            bool fuck = 1;
            for (int j = 1; j <= m; j++) {
                if (sta[i][j] == 0) {
                    fuck = 0;
                    break;
                }
            }
            if (fuck) {
                for (int j = 1; j <= m; j++) {
                    nsta[i][j] = 0;
                }
            }
        }
        for (int j = 1; j <= m; j++) {
            bool fuck = 1;
            for (int i = 1; i <= n; i++) {
                if (sta[i][j] == 0) {
                    fuck = 0;
                    break;
                }
            }
            if (fuck) {
                for (int i = 1; i <= n; i++) {
                    nsta[i][j] = 0;
                }
            }
        }
        swap(sta, nsta);
        return;
    };
    for (int i = 0; i < q; i++) {
        int nw = (s[i] == 'V');
        if (nw == 0) {
            // 1 * k
            bool use = 0;
            for (int row = 1; row <= n; row += n - 1) {
                if (row == 1) {
                    if (sta[row][m - k] == 2) {
                        int fuck = row;
                        while (fuck <= n && sta[fuck][m - k]) ++fuck;
                        --fuck;
                        doit(fuck, m - k + 1, 0);
                        use = 1;
                        break;
                    }
                } else {
                    if (sta[row][k + 1] == 2) {
                        int fuck = row;
                        while (fuck >= 1 && sta[fuck][k + 1]) --fuck;
                        ++fuck;
                        doit(fuck, 1, 0);
                        use = 1;
                        break;
                    }
                }
            }
            if (!use) {
                int width = 1;
                while (width <= k && sta[1][width] == 1) ++width;
                --width;
                if (width > 0 && width < k || sta[1][1] == 2) {
                    for (int row = n; row >= 1; row--) {
                        if (sta[row][m - k + 1] == 0) {
                            doit(row, m - k + 1, 0);
                            use = 1;
                            break;
                        }
                    }
                } else {
                    for (int row = 1; row <= n; row++) {
                        if (sta[row][1] == 0) {
                            doit(row, 1, 0);
                            use = 1;
                            break;
                        }
                    }
                }
            }
        } else {
            // k * 1
            bool use = 0;
            for (int col = m; col >= 1; col -= m - 1) {
                if (col == 1) {
                    if (sta[n - k][col] == 1) {
                        int fuck = col;
                        while (fuck <= m && sta[n - k][fuck]) ++fuck;
                        --fuck;
                        doit(n, fuck, 1);
                        use = 1;
                        break;
                    }
                } else {
                    if (sta[k + 1][col] == 2) {
                        int fuck = col;
                        while (fuck >= 1 && sta[k + 1][fuck]) --fuck;
                        ++fuck;
                        doit(k, col, 1);
                        use = 1;
                        break;
                    }
                }
            }
            if (!use) {
                int height = 1;
                while (height <= k && sta[n - height + 1][m] == 1) ++ height;
                --height;
                if (height > 0 && height < k || sta[n][m] == 1) {
                    for (int col = 1; col <= m; col++) {
                        if (sta[1][col] == 0) {
                            doit(k, col, 1);
                            use = 1;
                            break;
                        }
                    }
                } else {
                    for (int col = m; col >= 1; col--) {
                        if (sta[n][col] == 0) {
                            doit(n, col, 1);
                            use = 1;
                            break;
                        }
                    }
                }
            }
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