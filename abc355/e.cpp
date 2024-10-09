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

int ask(int l, int r) {
    cout << "? " << l << ' ' << r << endl;
    int x;
    cin >> x;
    return x;
}

void ouput(int val) {
    cout << "! " << val << endl;
    return;
}

void solve() {
    int n, l, r;
    cin >> n >> l >> r;
    int tmp = (r - l + 1), window = 0;
    int window = 1, bel_l, bel_r, c = 0;
    while (window * 2 <= tmp) {
        window *= 2;
        ++c;
    }
    bel_l = l / window;
    bel_r = r / window;
    int ans = 0;
    if (bel_l == bel_r) {
        ans = ask(c, bel_l);
        ouput(ans);
    } else {
        
    }
}

signed main() {
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    // int tt = 1;
    // cin >> tt;
    // while(tt--)
        solve();
    return 0;
}
