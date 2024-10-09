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
    vector<int> a(n + 5);
    vector<vector<int>> cnt(30, vector<int>(n + 5, 0));;
    int all = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        all |= a[i];
        for (int bit = 0; bit < 30; bit++) {
            cnt[bit][i + 1] = cnt[bit][i] + ((a[i] >> bit) & 1);
        }
    }
    auto chk = [&](int x) {
        for (int i = 1; i + x - 1 <= n; i++) {
            int cur = 0;
            for (int bit = 0; bit < 30; bit++) {
                if (cnt[bit][i + x - 1] - cnt[bit][i - 1] > 0) {
                    cur |= (1 << bit);
                }
            }
            if (cur != all) return 0;
        }
        return 1;
    };
    int l = 1, r = n, res = n;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (chk(mid)) res = mid, r = mid - 1;
        else l = mid + 1;
    }
    cout << res << '\n';
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
