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
    string s, t;
    cin >> s >> t;
    int n = s.length();
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) a[i] = s[i] - '0';
    for (int i = 0; i < n; i++) b[i] = t[i] - '0';
    map<vector<int>, int> dis;
    vector<vector<int>> que;
    map<vector<int>, vector<int>> prev;
    map<vector<int>, string> opt;
    dis[a] = 0;
    que.pb(a);
    for (int q = 0; q < que.size(); q++) {
        auto nw = que[q];
        int d = dis[nw];
        {
            auto nxt = nw;
            rotate(nxt.begin(), nxt.begin() + 1, nxt.end());
            if (!dis.count(nxt)) {
                dis[nxt] = d + 1;
                que.pb(nxt);
                prev[nxt] = nw;
                opt[nxt] = "l";
            }
        }
        {
            auto nxt = nw;
            rotate(nxt.begin(), nxt.begin() + n - 1, nxt.end());
            if (!dis.count(nxt)) {
                dis[nxt] = d + 1;
                que.pb(nxt);
                prev[nxt] = nw;
                opt[nxt] = "r";
            }
        }
        {
            auto nxt = nw;
            for (int i = 0; i < n; i++) {
                if (b[i] == 1) {
                    nxt[i] = 1 - nxt[i];
                    if (!dis.count(nxt)) {
                        dis[nxt] = d + 1;
                        que.pb(nxt);
                        prev[nxt] = nw;
                        opt[nxt] = "c";
                    }
                    nxt[i] = 1 - nxt[i];
                }
            }
        }
        if (dis.count(b)) {
            cout << dis[b] << '\n';
            auto print = [&](auto &&self, auto cur) -> void {
                if (prev.count(cur)) self(self, prev[cur]), cerr << opt[cur] << nl;
                for (int x : cur) cerr << x; cerr << nl;

            };
            print(print, b);
            return;
        }
    }
    cout << -1 << '\n';
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

/*
lllr
*/