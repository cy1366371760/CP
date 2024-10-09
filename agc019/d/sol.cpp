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
    string A, B;
    cin >> A >> B;
    int n = A.length();
    vector<int> a(n);
    vector<int> b(2 * n);
    for (int i = 0; i < n; i++) {
        a[i] = A[i] - '0';
    }
    for (int i = 0; i < 2 * n; i++) {
        b[i] = B[(i % n)] - '0';
    }
    if (*max_element(all(b)) == 0) {
        if (*max_element(all(a)) == 0) {
            cout << 0 << nl;
        } else {
            cout << -1 << nl;
        }
        return;
    }
    // cerr << "??" << nl;
    int ans = (int)1e9;
    for (int rev = 0; rev < 2; rev++) {
        for (int bias = 0; bias < n; bias++) {
            int lst = -1;
            int diff = 0;
            vector<pii> need(n, {0, 0});
            vector<bool> ok(n, 0);
            for (int i = 2 * n - 1; i >= 0; i--) {
                if (b[i] == 1) {
                    lst = i;
                }
                if (i < n && a[i] != b[i]) {
                    diff++;
                    if (lst - i <= bias) {
                        ok[i] = 1;
                    } else {
                        need[i].sc = lst - i - bias;
                    }
                }
            }
            lst = -1;
            for (int i = 0; i <= 2 * n - 1; i++) {
                if (b[i] == 1) {
                    lst = i;
                }
                if (i >= n && a[i - n] != b[i] && !ok[i - n]) {
                    need[i - n].fi = i - lst;
                }
            }
            sort(all(need));
            vector<int> suf(n + 1, (int)0);
            for (int i = n - 1; i >= 0; i--) {
                suf[i] = need[i].sc;
                chkmax(suf[i], suf[i + 1]);
            }
            int ex = (int)1e9;
            int pre = 0;
            for (int i = 0; i <= n; i++) {
                chkmin(ex, pre + suf[i]);
                if (i < n) chkmax(pre, need[i].fi);
            }
            chkmin(ans, diff + bias + ex * 2);
            chkmin(ans, diff + n + bias);
            rotate(a.begin(), a.begin() + 1, a.end());
        }
        reverse(all(A));
        for (int i = 0; i < n; i++) {
            a[i] = A[i] - '0';
        }
        reverse(all(B));
        for (int i = 0; i < 2 * n; i++) {
            b[i] = B[(i % n)] - '0';
        }
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