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
    string s;
    cin >> s;
    vector<char> ini(s.begin(), s.end());
    int n = s.length();
    for (int i = 0; i < n; i++) {
        ini[i] += 'a' - 'A';
    }
    map<vector<char>, bool> vis;
    auto dfs = [&](auto &&self, vector<char> cur) -> void {
        if (vis.count(cur)) return;
        vis[cur] = 1;
        int len = cur.size();
        for (int i = 0; i < len; i++) {
            cout << cur[i];
        }
        cout << nl;
        for (int i = 0; i + 1 < len; i++) {
            if (cur[i] == 's' && cur[i + 1] == 's') {
                vector<char> nxt(cur.begin(), cur.begin() + i);
                nxt.insert(nxt.end(), 'B');
                nxt.insert(nxt.end(), cur.begin() + i + 2, cur.end());
                self(self, nxt);
            }
        }
    };
    dfs(dfs, ini);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    // cin >> tt;
    // while(tt--)
        solve();
    return 0;
}