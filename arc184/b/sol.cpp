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
const int N = 1e9 + 100;
const int inf = 1e9;
const ll mod = 998244353;

void solve() {
    int n;
    cin >> n;
    int ans = 0;
    auto ask_cnt = [&](int x) {
        return x - x / 2 - x / 3 + x / 6;
    };
    auto sup_min = [&](int num, vector<int> &vals) {
        for (int bit = 0; bit < num; bit++) {
            for (int i = 0; i < vals.size(); i++) {
                if (i >> bit & 1) {
                    chkmin(vals[i ^ (1 << bit)], vals[i]);
                }
            }
        }
    };
    map<vector<int>, int> memo;
    auto calc = [&](int val) {
        int row = 0;
        int tmp = 1;
        while (tmp <= val / 2) {
            ++row, tmp *= 2;
        }
        vector<int> len(row + 1, 0);
        vector<int> sta(row + 1, 0);
        for (int r = 0, two = 1; r <= row; r++, two *= 2) {
            tmp = two;
            len[r] = 1;
            while (tmp <= val / 3) tmp *= 3, ++len[r];
            sta[r] = len[r];
        }
        if (memo.count(sta)) return memo[sta];
        vector<int> dp((1 << len[0]), inf);
        dp[0] = 0;
        vector<int> expand((1 << len[0]), 0);
        for (int i = 0; i < (1 << len[0]); i++) {
            int extra = 0;
            for (int bit = 0; bit < len[0]; bit++) {
                if (i >> bit & 1) extra |= (1 << (bit + 1));
            }
            expand[i] = i | extra;
        }
        for (int r = 0; r <= row; r++) {
            int all = (1 << len[r]) - 1;
            vector<int> dq(all + 1, inf);
            for (int i = 0; i <= all; i++) {
                int c = __builtin_popcount(i);
                int exist = all & expand[i];
                chkmin(dq[i], c + dp[all ^ exist]);
            }
            swap(dp, dq);
            sup_min(len[r], dp);
        }
        // cerr << "PP" << val << ' ' << *min_element(all(dp)) << nl;
        return memo[sta] = *min_element(all(dp));
    };
    for (int l = 1, r; l <= n; l = r + 1) {
        int val = n / l;
        r = n / val;
        ans += calc(val) * (ask_cnt(r) - ask_cnt(l - 1));
    }
    cout << ans << nl;
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