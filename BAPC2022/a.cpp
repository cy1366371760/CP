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
    ll xa;
    cin >> n >> k;
    cin >> xa;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    ld ans = fabs((ld)1.0 * accumulate(all(a), 0LL) / n - xa);
    ll sum = accumulate(all(a), 0LL);
    if (k >= 1) {
        ll need = sum - (n - 1) * xa;
        ll mn = 1e18;
        for (int i = 0; i < n; i++) {
            chkmin(mn, abs(need - a[i])); 
        }
        chkmin(ans, (ld)1.0 * mn / (n - 1));
    }
    if (k >= 2) {
        ll need = sum - (n - 2) * xa;
        ll mn = 1e18;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                chkmin(mn, abs(need - a[i] - a[j]));
            }
        }
        chkmin(ans, (ld)1.0 * mn / (n - 2));
    }
    auto ask_close = [&](set<ll> &st, ll val) {
        auto it = st.lower_bound(val);
        ll res = 1e18;
        if (it != st.end()) {
            res = (*it);
        }
        if (it != st.begin()) {
            --it;
            if (abs(res - val) > abs((*it) - val)) {
                res = (*it);
            }
        }
        return res;
    };
    if (k >= 3) {
        ll need = sum - (n - 3) * xa;
        ll mn = 1e18;
        set<ll> st;
        for (int i = 0; i < n; i++) {
            if (i >= 1) {
                for (int j = i + 1; j < n; j++) {
                    ll cur = a[i] + a[j];
                    ll rem = need - cur;
                    cur += ask_close(st, rem);
                    chkmin(mn, abs(need - cur));
                }
            }
            st.insert(a[i]);
        }
        chkmin(ans, (ld)1.0 * mn / (n - 3));
    }
    if (k >= 4) {
        ll need = sum - (n - 4) * xa;
        ll mn = 1e18;
        set<ll> st;
        for (int i = 0; i < n; i++) {
            if (i >= 2) {
                for (int j = i + 1; j < n; j++) {
                    ll cur = a[i] + a[j];
                    ll rem = need - cur;
                    cur += ask_close(st, rem);
                    chkmin(mn, abs(need - cur));
                }
            }
            for (int j = 0; j < i; j++) {
                st.insert(a[i] + a[j]);
            }
        }
        chkmin(ans, (ld)1.0 * mn / (n - 4));
    }
    cout << fixed << setprecision(10) << ans << nl;
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