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
    int n, s;
    cin >> n >> s;
    vector<array<int, 3>> seg(n);
    for (int i = 0; i < n; i++) {
        cin >> seg[i][0] >> seg[i][1];
        seg[i][2] = i;
    }
    /*
        [l, r]
        R >= s - r
        L <= s - l
        R min, 
    */
    sort(all(seg), [&](auto u, auto v){
        return u[0] == v[0] ? u[1] > v[1] : u[0] > v[0];
    });
    int ed = n;
    vector<pii> ans;
    set<pii> st;
    vector<bool> used(n, 0);
    for (int i = 0; i < n; i++) {
        auto [l, r, id] = seg[i];
        // cerr << l << ' ' << r << ' ' << id << nl;
        if (used[id]) continue;
        while (ed - 1 > i && seg[ed - 1][0] + l <= s) {
            --ed;
            st.insert(pii(seg[ed][1], seg[ed][2]));
        }
        st.erase(pii(r, id));
        auto ii = st.lower_bound(pii(s - r, -1));
        if (ii != st.end()) {
            ans.pb({id, (*ii).sc});
            used[(*ii).sc] = 1;
            st.erase(ii);
        }
    }
    cout << ans.size() << nl;
    for (auto [x, y] : ans) cout << x + 1 << ' ' << y + 1 << nl;
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