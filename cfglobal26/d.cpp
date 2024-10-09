#include<bits/stdc++.h>

#define int long long
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
    string s;
    cin >> s;
    int n = s.length();
    s = '#' + s;
    bool all_a = 1;
    for (int i = 1; i <= n; i++) {
        if (s[i] != 'a') {
            all_a = 0;
            break;
        }
    }
    if (all_a) {
        cout << n - 1 << '\n';
        return;
    }
    vector<int> cnt(30, 0);
    for (int i = 1; i <= n; i++) {
        cnt[s[i] - 'a']++;
    }
    int gcd = 0, num = 0;
    for (int i = 1; i < 26; i++) {
        gcd = __gcd(gcd, cnt[i]);
        if (cnt[i]) num++;
    }
    ll res = 0;
    auto doit = [&](int period) {
        auto each = cnt;
        for (int i = 1; i < 26; i++) {
            each[i] /= period;
        }
        vector<int> ed_ps;
        string las_t = "";
        ll fuck = 0;
        for (int i = 1; i <= n; i++) {
            if (s[i] != 'a') {
                int j = i;
                int need = num;
                auto las = each;
                string t = "";
                while (j <= n && need) {
                    las[s[j] - 'a']--;
                    if (s[j] != 'a' && las[s[j] - 'a'] == 0) {
                        need--;
                    }
                    if (s[j] != 'a' && las[s[j] - 'a'] < 0) return 0LL;
                    t += s[j];
                    j++;
                }
                ++fuck;
                if (need > 0) return 0LL;
                if (las_t == "") las_t = t;
                if (t != las_t) return 0LL;
                ed_ps.pb(j - 1);
                i = j - 1;
            }
        }
        if (fuck != period) return 0LL;
        int len = las_t.length();
        ll fr = 1e18, bk = 1e18, sm = 1e18;
        fr = ed_ps[0] - len;
        bk = n - ed_ps.back();
        for (int i = 0; i + 1 < ed_ps.size(); i++) {
            chkmin(sm, ed_ps[i + 1] - ed_ps[i] - len);
        }
        ll ans = 0;
        for (int i = 0; i <= fr && i <= sm; i++) {
            ans += min(bk, sm - i) + 1;
        }
        // cerr << "!!" << period << '\n';
        // for (auto x : ed_ps) cerr << x << ' ';
        // cerr << len << '\n';
        // cerr << fr << ' ' << bk << ' ' << sm << '\n';
        // cerr << '\n';
        return ans;
    };
    for (int d = 1; 1LL * d * d <= gcd; d++) {
        if (gcd % d == 0) {
            res += doit(d);
            if (1LL * d * d != gcd) {
                res += doit(gcd / d);
            }
        }
    }
    cout << res << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--)
        solve();
    return 0;
}
