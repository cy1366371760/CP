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
    vector<int> a(n + 5, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        for (int j = 1; j < a[i]; j++) {
            int _;
            cin >> _;
        }
    }
    sort(a.begin() + 1, a.begin() + n + 1);
    int cur = 0;
    for (int i = n; i >= 1; i--) {
        int best = cur;
        for (int j = 0; j <= a[i]; j++) {
            best = max(best, cur | j);
        }
        swap(cur, best);
    }
    cout << cur << '\n';
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
