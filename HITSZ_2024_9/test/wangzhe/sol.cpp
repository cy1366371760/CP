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
    map<string, int> idx;
    const int cnt = 10;
    for (int i = 1; i <= cnt; i++) {
        string name;
        cin >> name;
        idx[name] = i;
    }
    int n, m;
    cin >> n >> m;
    vector<int> las(15, (int)-1e9);
    vector<int> kill(15, 0);
    vector<int> res(15, 0);
    for (int i = 1; i <= n; i++) {
        int tim;
        string s, _;
        cin >> tim >> s >> _;
        int id = idx[s];
        if (tim - las[id] > m) {
            kill[id] = 1;
        } else {
            ++kill[id];
            if (kill[id] >= 5) {
                ++res[id];
            }
        }
        las[id] = tim;
    }
    for (int i = 1; i <= cnt; i++) {
        cout << res[i] << nl;
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