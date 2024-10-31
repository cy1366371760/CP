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
    int n, k;
    cin >> n >> k;
    int bas = 0;
    vector<int> cnt(k);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if (x % k == 0) {
            bas += (x / k - 1);
            continue;
        }
        bas += x / k;
        x %= k;
        if (x) cnt[x]++;
    }
    vector<vector<int>> split;
    vector<int> cur;
    int sum = 0;
    auto find_split = [&](auto &&self, int val) {
        if (sum == k) {
            split.pb(cur);
        }
        if (val + sum > k) return;
        self(self, val + 1);
        cur.pb(val);
        sum += val;
        self(self, val);
        sum -= val;
        cur.pop_back();
    };
    find_split(find_split, 1);
    vector<vector<pii>> real_split;
    for (auto s : split) {
        vector<int> cc(k + 1, 0);
        for (int x : s) cc[x]++;
        vector<pii> ss;
        for (int i = 1; i < k; i++) {
            if (cc[i]) {
                ss.pb({i, cc[i]});
            }
        }
        if (ss.empty()) continue;
        real_split.pb(ss);
    }
    map<vector<int>, int> vis;
    int ans = n, nw = 0;
    auto reducible = [&](vector<int> cur) -> bool {
        for (auto s : real_split) {
            bool ifok = 1;
            for (auto [x, c] : s) {
                if (cur[x] < c) {
                    ifok = 0;
                    break;
                }
            }
            if (ifok) {
                return 1;
            }
        }
        return 0;
    };
    // bfs
    {
        auto reduce = [&](vector<int> cur) {
            for (int i = 1; i <= k / 2; i++) {
                if (i == k - i) {
                    int del =   cur[i] / 2;
                    cur[i] -= del * 2;
                } else {
                    int del = min(cur[i],   cur[k - i]);
                    cur[i] -= del;
                    cur[k - i] -= del;
                }
            }
            return cur;
        };
        deque<pair<vector<int>, int>> que;
        cnt = reduce(cnt);
        vis[cnt] = 0;
        que.pb({cnt, 0});
        while (!que.empty()) {
            auto [cur, nw] = que.front();
            que.pop_front();
            if (*max_element(all(cur)) == 0) {
                cout << bas + nw << nl;
                exit(0);
            }
            if (vis[cur] != nw) continue;
            for (auto s : real_split) {
                bool ifok = 1;
                for (auto [x, c] : s) {
                    if (cur[x] < c) {
                        ifok = 0;
                        break;
                    }
                }
                if (ifok) {
                    for (auto [x, c] : s) {
                        cur[x] -= c;
                    }
                    if (!vis.count(cur) || vis[cur] > nw) {
                        vis[cur] = nw;
                        que.push_front({cur, nw});
                    }
                    for (auto [x, c] : s) {
                        cur[x] += c;
                    }
                }
            }
            for (int i = k - 1; i >= 2; i--) {
                if (cur[i] > 0) {
                    for (int j = 1; j <= i / 2; j++) {
                        --cur[i];
                        ++cur[j];
                        ++cur[i - j];
                        auto nxt = reduce(cur);
                        if (!vis.count(nxt)) {
                            vis[nxt] = nw + 1;
                            que.push_back({nxt, nw + 1});
                        }
                        ++cur[i];
                        --cur[j];
                        --cur[i - j];
                    }
                    break;
                }
            }
        }
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