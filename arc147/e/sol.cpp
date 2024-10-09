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

void solve() {
    int n;
    cin >> n;
    vector<pii> vals(n);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> vals[i].fi >> vals[i].sc;
        swap(vals[i].fi, vals[i].sc);
        a[i] = vals[i].fi;
    }
    sort(all(a));
    map<int, int> use;
    vector<pii> sel(n);
    vector<int> maybe(n, -1);
    for (int i = 0; i < n; i++) {
        int b = upper_bound(all(a), vals[i].sc) - a.begin() - 1;
        int gain = lower_bound(all(a), vals[i].fi) - a.begin();
        gain += use[vals[i].fi];
        use[vals[i].fi]++;
        sel[i] = pii(b, gain);
        if (gain <= b) {
            maybe[gain] = b;
        }
    }
    sort(all(sel));
    vector<int> unachiv;
    set<pii> achiv;
    vector<bool> hav(n, 0);
    int ptr = 0;
    int res = 0;
    for (auto [b, gain] : sel) {
        while (ptr <= b) {
            if (maybe[ptr] != -1) {
                achiv.insert(pii(maybe[ptr], ptr));
            } else {
                unachiv.pb(ptr);
            }
            hav[ptr] = 1;
            ptr++;
        }
        /*
            1.use gain
            2.use one unachievable
            3.use one achievable with biggest corresponding b
        */
       if (hav[gain]) {
            ++res;
            achiv.erase(pii(b, gain));
            hav[gain] = 0;
       } else if (unachiv.size()) {
            int nw = unachiv.back();
            unachiv.pop_back();
            hav[nw] = 0;
       } else {
            if (achiv.empty()) {
                cout << -1 << '\n';
                return;
            }
            auto ii = prev(achiv.end());
            auto [_, id] = (*ii);
            hav[id] = 0;
            achiv.erase(ii);
       }
    }
    cout << res << '\n';
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