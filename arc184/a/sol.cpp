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
    int n, m, q;
    cin >> n >> m >> q;
    auto is_dif = [&](int x, int y) {
        if (x == y) return 0;
        cout << "? " << x << ' ' << y << endl;
        int re;
        cin >> re;
        return re;
    };
    int may_sz = 0;
    vector<pair<vector<int>, vector<int>>> maybe;
    vector cur(n, vector<int>());
    for (int i = 1; i <= n; i++) {
        cur[i - 1].pb(i);
    }
    while (may_sz < m) {
        vector<vector<int>> nxt;
        for (int i = 0; i < cur.size(); i += 2) {
            if (may_sz >= m) {
                if (i == cur.size() - 1) nxt.pb(cur[i]);
                else nxt.pb(cur[i]), nxt.pb(cur[i + 1]);
                continue;
            }
            if (i == cur.size() - 1) {
                auto fir = nxt.back();
                nxt.pop_back();
                auto sec = cur[i];
                int dif = is_dif(fir[0], sec[0]);
                if (dif) {
                    may_sz += min(fir.size(), sec.size());
                    maybe.pb(make_pair(fir, sec));
                } else {
                    fir.insert(fir.end(), all(sec));
                    nxt.pb(fir);
                }
                continue;
            }
            auto fir = cur[i];
            auto sec = cur[i + 1];
            int dif = is_dif(fir[0], sec[0]);
            if (dif) {
                may_sz += min(fir.size(), sec.size());
                maybe.pb(make_pair(fir, sec));
            } else {
                fir.insert(fir.end(), all(sec));
                nxt.pb(fir);
            }
        }
        swap(cur, nxt);
    }
    // for (int i = 0; i < cur.size(); i++) {
    //     cerr << "fuck" << i << nl;
    //     for (int x : cur[i]) cerr << x << ' ';
    //     cerr << nl;
    // }
    vector<int> ans;
    int good = cur[0][0];
    for (auto [fir, sec] : maybe) {
        // cerr << "shit" << nl;
        // for (int x : fir) cerr << x << ' ' ; cerr << nl;
        // for (int x : sec) cerr << x << ' ' ; cerr << nl;
        int bad_fir = is_dif(fir[0], good);
        if (bad_fir) {
            ans.insert(ans.end(), all(fir));
        } else {
            ans.insert(ans.end(), all(sec));
        }
    }
    assert(ans.size() == m);
    cout << "! ";
    for (int x : ans) cout << x << ' ';
    cout << endl;
}

signed main() {
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    // int tt = 1;
    // cin >> tt;
    // while(tt--)
        solve();
    return 0;
}