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
    int n, qq;
    cin >> n >> qq;
    vector<ll> a(n + 5);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    while (qq--) {
        int l, r;
        cin >> l >> r;
        if (r - l + 1 >= 50) {
            cout << "YES" << '\n';
        } else {
            vector<ll> cur;
            for (int i = l; i <= r; i++) {
                cur.pb(a[i]);
            }
            sort(all(cur));
            // for (int x : cur) cerr <<  x << ' ';
            auto chk = [&](int i, int j, int k) {
                if (i < 0 || k >= cur.size()) return false;
                assert(i < j && j < k);
                return (cur[i] + cur[j] > cur[k] ? true : false);
            };
            bool ok = false;
            for (int i = 1; i < cur.size(); i++) {
                for (int j = max(3, i + 1); j < cur.size() - 1; j++) {
                    if (j - i >= 3) {
                        ok |= chk(i - 1, i, i + 1) && chk(j - 1, j, j + 1);
                    } else {
                        if (j - i == 1) {
                            vector<int> lhs = {i - 2, i - 1};
                            vector<int> rhs = {j + 1, j + 2};
                            for (int l = 0; l < 2; l++) {
                                for (int r = 0; r < 2; r++) {
                                    ok |= chk(lhs[l], i, rhs[r]) && chk(lhs[1 - l], j, rhs[1 - r]);
                                }
                            }
                        } else {
                            vector<int> lhs = {i - 2, i - 1};
                            vector<int> rhs = {j + 1, j + 2};
                            int mid = i + 1;
                            for (int l = 0; l < 2; l++) {
                                for (int r = 0; r < 2; r++) {
                                    ok |= chk(lhs[l], i, rhs[r]) && chk(lhs[1 - l], j, rhs[1 - r]);
                                    ok |= chk(lhs[l], i, mid) && chk(lhs[1 - l], j, rhs[1 - r]);
                                    ok |= chk(lhs[l], i, rhs[r]) && chk(mid, j, rhs[1 - r]);
                                }
                            }
                        }
                    }
                    if (ok) break;
                }
                if (ok) break;
            }
            cout << (ok ? "YES" : "NO") << '\n';
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