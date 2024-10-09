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
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> imp(k + 1, 0);
    for (int i = 1; i <= k; i++) {
        cin >> imp[i];
    }
    vector adj(n + 1, vector<int>());
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    vector<int> dis_n(n + 5, -1), dis_1(n + 5, -1);
    {
        vector<int> que;
        auto &dis = dis_n;
        que.pb(n);
        dis[n] = 0;
        for (int q = 0; q < que.size(); q++) {
            int x = que[q];
            for (int y : adj[x]) {
                if (dis[y] == -1) {
                    dis[y] = dis[x] + 1;
                    que.pb(y);
                }
            }
        }
    }
    {
        vector<int> que;
        auto &dis = dis_1;
        que.pb(1);
        dis[1] = 0;
        for (int q = 0; q < que.size(); q++) {
            int x = que[q];
            for (int y : adj[x]) {
                if (dis[y] == -1) {
                    dis[y] = dis[x] + 1;
                    que.pb(y);
                }
            }
        }
    }
    ll res_son = dis_1[n], res_mother = 1;
    ll sum_dis = 0;
    for (int i = 1; i <= k; i++) {
        sum_dis += dis_n[imp[i]];
    }
    for (int i = 1; i <= k; i++) {
        int x = imp[i];
        // dis_1[x]
        // (sum_dis - dis_n[imp[i]]) / (k - 1)
        ll mother = k - 1;
        ll son = (k - 1) * dis_1[x] + (sum_dis - dis_n[imp[i]]);
        ll g = __gcd(son, mother);
        son /= g;
        mother /= g;
        if (son * res_mother <= res_son * mother) {
            res_son = son;
            res_mother = mother;
        }
    }
    cout << res_son << "/" << res_mother << nl;
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