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
    int n, W;
    cin >> n >> W;
    int sam = n * 2 / 3;
    vector<pii> ans(n + 5);
    int d = -1;
    for (int i = n; i > sam; i--) {
        ++d;
        ans[i] = pii(d, d);
    }
    int bias = sam + 5;
    for (int i = 1; i <= sam; i++) {
        ans[i] = pii(d - i + bias, d + i);
    }
    auto fuck = [&](vector<pii> cur) {
        vector<int> sta(n + 5, 0);
        int step = 0;
        for (int r = 1; r <= n; r++) {
            for (int i = 1; i <= n; i++) {
                if (!sta[i]) {
                    for (int j = i + 1; j <= n; j++) {
                        if (!sta[j]) {
                            ++step;
                            if (cur[i].fi < cur[j].fi && cur[i].sc < cur[j].sc) {
                                sta[j] = 1;
                            }
                            if (cur[i].fi > cur[j].fi && cur[i].sc > cur[j].sc) {
                                sta[i] = 1;
                                break;
                            }
                        }
                    }
                    if (!sta[i]) sta[i] = 2;
                }
            }
            for (int i = 1; i <= n; i++) {
                if (sta[i] == 1) sta[i] = 0;
            }
        }
        return step;
    };
    cerr << fuck(ans) << ' ' << n * n * n / 20 << '\n';
    cerr << fuck(ans) - (n * n * n / 20) << '\n';
    for (int i = 1; i <= n; i++) {
        auto [w, q] = ans[i];
        if (W >= d + bias) {
            cout << W - w << ' ' << 1000 - q << '\n';
        } else {
            cout << W + w << ' ' << 1000 - q << '\n';
        }
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