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
    vector<int> a(n);
    for (int &x : a)
        cin >> x;
    if (a[0] == a[n - 1]) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    map<int, int> cnt;
    for (int i = 0; i < n; ++i) {
        cnt[a[i]]++;
    }
    int who = a[0];
    for (int i = 1; i < n; ++i) {
        if (cnt[a[i]] > cnt[who]) {
            who = a[i];
        }
    }
    bool flg = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == who && flg == 0) {
            cout << 'R';
            flg = 1;
        } else {
            cout << 'B';
        }
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
