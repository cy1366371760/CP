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

struct Sta {
    deque<int> dq;
    array<ll, 3> cnt;
    vector<pii> unstable;
    Sta () {
        cnt = {0, 0, 0};
    }
    int is_unstable(int a, int b, int c) {
        if (b == 1 && a == 0 && c == 0) return 1;
        if (b == 2) {
            if (a > c) swap(a, c);
            if (a == 0 && c == 0) return 2;
            if (a >= 1) return 1;
        }
        return 0;
    }
    void nxt() {
        if (dq.empty()) return;
        if (dq.size() == 1) {
            --cnt[dq[0]];
            dq.pop_back();
            return;
        }
        for (auto[i, del] : unstable) {
            --cnt[dq[i]];
            dq[i] -= del;
            ++cnt[dq[i]];
        }
        unstable.clear();
        --cnt[dq[0]];
        --cnt[dq.back()];
        dq.pop_back();
        dq.pop_front();
    }
    void append(int fir, int las) {
        dq.push_front(fir);
        ++cnt[fir];
        if (dq.size() >= 3 && is_unstable(dq[0], dq[1], dq[2])) {
            unstable.pb({1, is_unstable(dq[0], dq[1], dq[2])});
        }
        dq.push_back(las);
        ++cnt[las];
        if (dq.size() >= 3 && is_unstable(dq.end()[-3], dq.end()[-2], dq.end()[-1])) {
            unstable.pb({dq.size() - 2, is_unstable(dq.end()[-3], dq.end()[-2], dq.end()[-1])});
        }
    }
};


array<ll, 3> operator + (array<ll, 3> a, array<ll, 3> b) {
    return {a[0] + b[0], a[1] + b[1], a[2] + b[2]};
}

void solve() {
    ll n;
    cin >> n;
    auto mex = [&](int x, int y) {
        vector<bool> vis(3, 0);
        vis[x] = 1;
        vis[y] = 1;
        for (int i = 0; i < 3; i++) {
            if (!vis[i]) return i;
        }
    };
    auto brute = [&](int n) {
        vector a(n + 5, vector<int>(n + 5, 0));
        for (int j = 1; j <= n; j++) {
            cin >> a[1][j];
        }
        for (int i = 2; i <= n; i++) {
            cin >> a[i][1];
        }
        for (int i = 2; i <= n; i++) {
            for (int j = 2; j <= n; j++) {
                a[i][j] = mex(a[i - 1][j], a[i][j - 1]);
            }
        }
        vector<int> cnt(3, 0);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                ++cnt[a[i][j]];
                cerr << a[i][j] << ' ';
            }
            cerr << nl;
        }
        return array<int, 3>{cnt[0], cnt[1], cnt[2]};
    };
    if (n <= 114514) { // brute force
        auto res = brute(n);
        cout << res[0] << ' ' << res[1] << ' ' << res[2] << nl;
        return;
    }
    vector<int> fst(n + 1, 0);
    vector<int> lst(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> lst[i];
    }
    for (int i = 2; i <= n; i++) {
        cin >> fst[i];
    }
    array<ll, 3> res = {0, 0, 0};
    Sta sta[2];
    vector<int> laz;
    for (int i = 1; i <= 2 * n - 1; i++) {
        int op = (i & 1);
        if (i == 1) {
            sta[op].dq.push_back(lst[i]);
            ++sta[op].cnt[lst[i]];
        } else {
            sta[op].nxt();
            if (laz.size() == 1) {
                int x = laz[0];
                laz.clear();
                sta[op].dq.push_back(x);
                ++sta[op].cnt[x];
            } else if (laz.size() == 2) {
                sta[op].append(laz[0], laz[1]);
                laz.clear();
            }
            if (i <= n) {
                sta[op].append(fst[i], lst[i]);
                if (sta[op].dq.size() == 2) {
                    laz.pb(mex(sta[op].dq[0], sta[op].dq[1]));
                } else {
                    laz.pb(mex(sta[op].dq[0], sta[op].dq[1]));
                    laz.pb(mex(sta[op].dq.end()[-2], sta[op].dq.end()[-1]));
                }
            }

        }
        res = res + sta[op].cnt;
        // cerr << "!!" << i << ' ' << sta[op].cnt[0] << ' ' << sta[op].cnt[1] << ' ' << sta[op].cnt[2] << nl;
    }
    cout << res[0] << ' ' << res[1] << ' ' << res[2] << nl;
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