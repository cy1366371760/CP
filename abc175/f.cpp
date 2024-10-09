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
const int N = 60, L = 25;
const ll inf = 1e18;
const ll mod = 998244353;

ll dis[N * 2 * L];
int idx[N][2][L], tot = 1;

vector<pll> adj[N * 2 * L];

void solve() {
    int n;
    cin >> n;
    vector<string> s(n + 5);
    vector<ll> c(n + 5);
    for (int i = 0; i < n; i++) {
        cin >> s[i] >> c[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < s[i].length(); k++) {
                idx[i][j][k] = tot++;
            }
        }
    }

    auto get_nxt = [&](int p, int tp, int ps, int l, int q) {
        if (tp == 0) {
            int p_to = ps - l;
            int q_to = l;
            if (p_to < 0 && q_to >= s[q].length()) {
                return 0;
            } else if (p_to >= 0 && q_to < s[q].length()) {
                return -1;
            } else if (p_to >= 0) {
                return idx[p][0][p_to];
            } else {
                return idx[q][1][q_to];
            }
        } else {
            int p_to = ps + l;
            int q_to = s[q].length() - 1 - l;
            if (p_to >= s[p].length() && q_to < 0) {
                return 0;
            } else if (p_to < s[p].length() && q_to >= 0) {
                return -1;
            } else if (p_to < s[p].length()) {
                return idx[p][1][p_to];
            } else {
                return idx[q][0][q_to];
            }
        }
    };

    for (int p = 0; p < n; p++) {
        auto &a = s[p];
        for (int ps = 0; ps < a.length(); ps++) {
            for (int q = 0; q < n; q++) {
                int nw = idx[p][0][ps];
                auto &b = s[q];
                int l = 0;
                while (ps - l >= 0 && l < b.length() && a[ps - l] == b[l]) l++;
                int nxt = get_nxt(p, 0, ps, l, q);
                if (nxt != -1) {
                    adj[nw].eb(nxt, c[q]);
                }
                l = 0;
                while (ps + l < a.length() && l < b.length() && a[ps + l] == b[b.length() - 1 - l]) l++;
                nw = idx[p][1][ps];
                nxt = get_nxt(p, 1, ps, l, q);
                if (nxt != -1) {
                    adj[nw].eb(nxt, c[q]);
                }
            }
        }
    }
    memset(dis, 63, sizeof dis);
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    auto upd = [&](ll id, ll v) {
        if (dis[id] <= v) return;
        dis[id] = v;
        pq.push({v, id});
    };
    for (int p = 0; p < n; p++) {
        int len = s[p].length();
        for (int axis = 0; axis < len; axis++) {
            bool ifok = 1;
            for (int j = 0; axis - j >= 0 && axis + j < len; j++) {
                if (s[p][axis - j] != s[p][axis + j]) {
                    ifok = 0;
                    break;
                }
            }
            if (ifok) {
                int left = axis;
                int right = len - 1 - axis;
                if (left == right) 
                    upd(0, c[p]);
                if (left > right) 
                    upd(idx[p][0][s[p].length() - 1 - 1 - 2 * right], c[p]);
                if (left < right)
                    upd(idx[p][1][0 + 1 + 2 * left], c[p]);
            }
        }
        for (int axis = 0; axis <= len; axis++) {
            bool ifok = 1;
            for (int j = 0; axis - 1 - j >= 0 && axis + j < len; j++) {
                if (s[p][axis - 1 - j] != s[p][axis + j]) {
                    ifok = 0;
                    break;
                }
            }
            if (ifok) {
                int left = axis;
                int right = len - axis;
                if (left == right) 
                    upd(0, c[p]);
                if (left > right) 
                    upd(idx[p][0][s[p].length() - 1 - 2 * right], c[p]);
                if (left < right)
                    upd(idx[p][1][0 + 2 * left], c[p]);
            }
        }
    }
    while (!pq.empty()) {
        auto [d, id] = pq.top();
        pq.pop();
        if (dis[id] != d) continue;
        for (auto [to, w] : adj[id]) {
            upd(to, d + w);
        }
    }
    if (dis[0] >= inf) dis[0] = -1;
    cout << dis[0] << '\n';
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
