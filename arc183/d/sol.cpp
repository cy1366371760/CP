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
    vector<int> cnt(n + 1, k);
    if (n & 1) {
        int mid = (n + 1) / 2;
        while (cnt[mid]) {
            cnt[mid]--;
            cout << mid << ' ';
        }
        if (n == 1) return;
        --mid;
        cout << mid << ' ';
        cnt[mid]--;
        for (int i = n; i >= 1; i--) {
            for (int j = 1; j <= cnt[i]; j++) {
                cout << i << ' ';
            }
        }
    }
    if (n % 2 == 0) {
        cout << n / 2 << ' ';
        cnt[n / 2]--;
        for (int i = n; i >= 1; i--) {
            for (int j = 1; j <= cnt[i]; j++) {
                cout << i << ' ';
            }
        }
        cout << '\n';
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