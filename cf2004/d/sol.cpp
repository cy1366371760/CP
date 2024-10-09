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
const int inf = 1e8;
const ll mod = 998244353;

void solve() {
    int n, qq;
    cin >> n >> qq;
    vector<string> col(n);
    map<string, int> las;
    vector<int> go_l(n), go_r(n);
    for (int i = 0; i < n; i++) {
        cin >> col[i];
    }
    vector<string> may{"BG", "BR", "BY", "GR", "GY", "RY"};
    for (auto str : may) {
        las[str] = -inf;
    }
    for (int i = 0; i < n; i++) {
        int res = -inf;
        for (auto str : may) {
            if (str != col[i]) {
                bool flg = 0;
                for (int j = 0; j < 2; j++) {
                    for (int k = 0; k < 2; k++) {
                        if (str[j] == col[i][k]) flg = 1;
                    }
                }
                if (flg) chkmax(res, las[str]);
            }
        }
        go_l[i] = res;
        las[col[i]] = i;
    }
    for (auto str : may) {
        las[str] = inf;
    }
    for (int i = n - 1; i >= 0; i--) {
        int res = inf;
        for (auto str : may) {
            if (str != col[i]) {
                bool flg = 0;
                for (int j = 0; j < 2; j++) {
                    for (int k = 0; k < 2; k++) {
                        if (str[j] == col[i][k]) flg = 1;
                    }
                }
                if (flg) chkmin(res, las[str]);
            }
        }
        go_r[i] = res;
        las[col[i]] = i;
    }
    auto fuck = [&](int x, int y, int z) {
        return abs(x - y) + abs(y - z);
    };
    while (qq--) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        if (x > y) swap(x, y);
        bool flg = 0;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                if (col[x][i] == col[y][j]) {
                    flg = 1;
                    cout << y - x << '\n';
                    break;
                }
            }
            if (flg) {
                break;
            }
        }
        if (flg) continue;
        int ans = min({fuck(x, go_l[x], y), fuck(x, go_r[x], y), fuck(x, go_l[y], y), fuck(x, go_r[y], y)});
        if (ans >= 4 * n) ans = -1;
        cout << ans << '\n';
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