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
    int n, k;
    cin >> n >> k;
    vector<int> R(n);
    for (int i = 0; i < n; i++) {
        cin >> R[i];
    }
    vector<int> cur(n);
    auto dfs = [&](auto &&self, int x) -> void {
        if (x == n) {
            int sum = accumulate(all(cur), 0);
            if (sum % k == 0) {
                for (int i = 0; i < n; i++) {
                    cout << cur[i] << " \n"[i == n - 1];
                }
            }
            return;
        }
        for (int i = 1; i <= R[x]; i++) {
            cur[x] = i;
            self(self, x + 1);
        }
    };
    dfs(dfs, 0);
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