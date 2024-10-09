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
const int N = 1e6 + 100;
const ll inf = 1e18;
const ll mod = 998244353;

struct CombineSet {
    set<int> st;
    int cnt[N];
    void ins(int x) {
        ++cnt[x];
        if (cnt[x] == 1) {
            st.insert(x);
        }
    }
    void del(int x) {
        --cnt[x];
        if (cnt[x] == 0) {
            st.erase(x);
        }
    }
    int size() {
        return st.size();
    }
};

void solve() {
    int n;
    cin >> n;
    // int n = 4;
    vector<int> a(n + 2);
    vector hav(n + 2, vector<int>());
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        // lb:
        // a[i] = rand() % n + 1;
        // if (a[i] == i) goto lb;
        hav[a[i]].pb(i);
    }
    for (int i = 0; i <= n; i++) {
        sort(all(hav[i]));
        reverse(all(hav[i]));
    }
    if (n == 2) {
        cout << -1 << '\n';
        return;
    }
    CombineSet after;
    set<pii> pq;
    for (int i = 1; i <= n; i++) {
        after.ins(a[i]);
    }
    vector<bool> vis(n + 2, 0);
    for (int i = 1; i <= n; i++) {
        if (hav[i].size()) {
            pq.insert(pii(hav[i].back(), i));
            // cerr << "miao" << hav[i].back() << ' ' << i << '\n';
        }
    }
    auto chk = [&](int x, int ban, int las) {
        if (vis[ban]) {
            // cerr << "???" << after.size() << ' ' << las << '\n';
            int res = 1;
            after.del(ban);
            vis[x] = 1;
            if (after.size() == 2 && las == 2) {
                auto ii = (*after.st.begin());
                auto jj = (*after.st.rbegin());
                if (!vis[ii] && !vis[jj]) res = 0;
            }
            after.ins(ban);
            vis[x] = 0;
            return res;
        }
        after.del(a[ban]);
        int res = 1;
        if (after.size() == 1 && (*after.st.begin() == ban)) {
            res = 0;
        }
        after.ins(a[ban]);
        after.del(ban);
        vis[x] = 1;
        if (after.size() == 2 && las == 2) {
            auto ii = (*after.st.begin());
            auto jj = (*after.st.rbegin());
            if (!vis[ii] && !vis[jj]) res = 0;
        }
        after.ins(ban);
        vis[x] = 0;
        return res;
    };
    int bf_ban = -1;
    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        vector<pii> bin;
        pii special = pii(-1, -1);
        while (1) {
            if (pq.empty()) {
                assert(0);
                return;
            }
            auto [x, ban] = *pq.begin();
            pq.erase(pq.begin());
            if (bf_ban == x) {
                special = pii(x, ban);
                hav[ban].pop_back();
                if (hav[ban].size()) {
                    pq.insert({hav[ban].back(), ban});
                }
                continue;
            }
            if (chk(x, ban, n - i) == 0) {
                bin.pb({x, ban});
                continue;
            }
            vis[x] = 1;
            hav[ban].pop_back();
            if (hav[ban].size()) {
                pq.insert({hav[ban].back(), ban});
            }
            ans.pb(x);
            after.del(ban);
            bf_ban = ban;
            break;
        }
        for (auto [x, ban] : bin) {
            pq.insert({x, ban});
        }
        if (special != pii(-1, -1)) {
            if (hav[special.sc].size()) {
                pq.erase(pii(hav[special.sc].back(), special.sc));
            }
            pq.insert(special);
            hav[special.sc].pb(special.fi);
        }
    }
    for (auto x : ans) cout << x << ' ';
    cout << '\n';
}

signed main() {
    srand(time(0));
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    // cin >> tt;
    // while(tt--)
        solve();
    return 0;
}