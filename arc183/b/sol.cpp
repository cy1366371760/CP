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
    vector<int> a(n + 5);
    vector<int> b(n + 5);
    vector<int> visa(n + 5, 0);
    vector<int> visb(n + 5, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        visa[a[i]]++;
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        visb[b[i]]++;
    }
    bool all_same = 1;
    for (int i = 1; i <= n; i++) {
        if (a[i] != b[i]) all_same = 0;
    }
    if (all_same) {
        cout << "Yes" << '\n';
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (visb[i] && !visa[i]) {
            cout << "No" << '\n';
            return;
        }
    }
    if (k == 1) {
        int b_ps = 1;
        for (int i = 1; i <= n; i++) {
            while (b_ps <= n && b[b_ps] == a[i]) ++b_ps;
        }
        if (b_ps > n) {
            cout << "Yes" << '\n';
        } else {
            cout << "No" << '\n';
        }
    } else {
        bool exist_good = 0;
        vector<int> las(n + 5, (int)-1e9);
        for (int i = 1; i <= n; i++) {
            int nw = b[i];
            if (las[nw] + k >= i) exist_good = 1;
            las[nw] = i;
        }
        las = vector<int>(n + 5, (int)1e9);
        for (int i = n; i >= 1; i--) {
            int nw = b[i];
            if (las[nw] - k <= i) exist_good = 1;
            las[nw] = i;
        }
        if (!exist_good) {
            cout << "No" << '\n';
            return;
        }
        bool flg = 0;
        for (int i = 1; i <= n; i++) {
            --visa[a[i]];
            if (visa[a[i]] || !visb[a[i]]) {
                flg = 1;
            }
            ++visa[a[i]];
        }
        if (flg) {
            cout << "Yes" << '\n';
        } else {
            cout << "No" << '\n';
        }
    }
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