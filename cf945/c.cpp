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
    vector<int> p(n + 5);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    int type;
    for (int i = 1; i <= n; i++) {
        if (p[i] == 1) {
            type = i & 1;
        }
    }
    vector<pii> small, large;
    for (int i = 1; i <= n; i++) {
        if ((i & 1) == type) {
            small.eb(p[i], i);
        } else {
            large.eb(p[i], i);
        }
    }
    sort(all(small));
    reverse(all(small));
    sort(all(large));
    vector<int> ans(n + 5, 0);
    for (int i = 0; i < small.size(); i++) {
        ans[small[i].sc] = i + 1;
    }
    for (int i = 0; i < large.size(); i++) {
        ans[large[i].sc] = n - i;
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
    
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
