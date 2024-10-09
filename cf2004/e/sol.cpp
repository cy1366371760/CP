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
const int N = 1e7 + 100;
const ll inf = 1e18;
const ll mod = 998244353;

bool np[N];
int pnum = 0;
int pri[N / 2], sg[N];

void init() {
    int n = 1e7;
    for (int i = 2; i <= n; i++) {
        if (!np[i]) pri[++pnum] = i;
        for (int j = 1; j <= pnum && 1LL * pri[j] * i <= n; j++) {
            np[i * pri[j]] = 1;
            if (i % pri[j] == 0) break;
        }
    }
    sg[1] = 1;
    for (int i = 2; i <= pnum; i++) {
        int p = pri[i];
        for (int j = p; j <= n; j += 2 * p) {
            if (!sg[j]) {
                sg[j] = i;
            }
        }
    }
    // for (int i = 0; i <= 100; i++) {
    //     cerr << i << ' ' << sg[i] << '\n';
    // }
}

void solve() {
    // int n = 100; // sg[3 + 6k] = 2, sg[5 + 10k] = 3, sg[7 + 14k] = 4, sg[11 + 22k] = 5
    // vector<int> sg(n + 10, 0);
    // sg[1] = 1;
    // for (int i = 2; i <= n; i++) {
    //     vector<bool> vis(i + 5, 0);
    //     for (int j = 1; j < i; j++) {
    //         if (__gcd(i, j) == 1) {
    //             vis[sg[i - j]] = 1;
    //         }
    //     }
    //     for (int j = 0; j <= i; j++) {
    //         if (!vis[j]) {
    //             sg[i] = j;
    //             break;
    //         }
    //     }
    //     cerr << i << ' ' << sg[i] << '\n';
    // }
    int n;
    cin >> n;
    int res = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        res ^= sg[x];
    }
    cout << (res ? "Alice" : "Bob") << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    init();
    while(tt--)
        solve();
    return 0;
}