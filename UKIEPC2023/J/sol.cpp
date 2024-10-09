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

struct Flight {
    int s, t;
    int st, ed;
    int id;
}flight[N];

void solve() {
    int n;
    cin >> n;
    vector<string> s(n + 5), t(n + 5);
    vector<int> st(n + 5), ed(n + 5);
    auto get_tim = [&](string s) {
        int dd = 0;
        int hh = 0;
        int mm = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == 'd') {
                for (int j = 0; j < i; j++) {
                    dd = dd * 10 + s[j] - '0';
                }
                bool fl = 0;
                for (int j = i + 1; j < s.length(); j++) {
                    if (s[j] == ':') {
                        fl = 1;
                        continue;
                    }
                    if (fl == 0) {
                        hh = hh * 10 + s[j] - '0';
                    } else {
                        mm = mm * 10 + s[j] - '0';
                    }
                }
                break;
            }
        }
        return dd * 24 * 60 + hh * 60 + mm;
    };
    int tot = 0;
    map<string, int> sidx;
    for (int i = 1; i <= n; i++) {
        string de, ar;
        cin >> s[i] >> de >> t[i] >> ar;
        st[i] = get_tim(de);
        ed[i] = get_tim(ar);
        if (!sidx.count(s[i])) sidx[s[i]] = ++tot;
        if (!sidx.count(t[i])) sidx[t[i]] = ++tot;
        flight[i].id = i;
        flight[i].s = sidx[s[i]];
        flight[i].t = sidx[t[i]];
        flight[i].st = st[i];
        flight[i].ed = ed[i];
        // cerr << i << ' ' << flight[i].s << ' ' << flight[i].t << '\n';
    }
    int m;
    cin >> m;
    vector<int> who(m + 5);
    vector<int> imp(n + 5, 0);
    for (int i = 0; i < m; i++) {
        cin >> who[i];
        imp[who[i]] = 1;
    }
    int dest = flight[who[m - 1]].t;
    // cerr << "??" << ' ' << dest << '\n';
    int plan = flight[who[m - 1]].ed;

    sort(flight + 1, flight + n + 1, [&](Flight a, Flight b){
        return a.st == b.st ? imp[a.id] > imp[b.id] : a.st < b.st;
    });
    vector<int> rnk(n + 5);
    for (int i = 1; i <= n; i++) {
        rnk[flight[i].id] = i;
    }
    vector<set<pii>> dp(n + 5);
    auto ask = [&](int ps, int tim) {
        if (ps == dest) return tim;
        auto ii = dp[ps].lower_bound(pii(tim, -1));
        if (ii == dp[ps].end()) return (int)1e9;
        return (*ii).sc;
    };
    auto update = [&](int ps, int tim, int val) {
        auto ii = dp[ps].begin();
        if (ii == dp[ps].end() || (*ii).sc > val) {
            dp[ps].insert(pii(tim, val));
        }
    };
    int ans = 0;
    for (int i = n; i >= 1; i--) {
        // cerr << i << ' ' << flight[i].id << ' ' << imp[flight[i].id] << '\n';
        if (imp[flight[i].id]) {
            chkmax(ans, ask(flight[i].s, flight[i].st));
        }
        int tmp = ask(flight[i].t, flight[i].ed);
        update(flight[i].s, flight[i].st, tmp);
    }
    if (ans == (int)1e9) {
        cout << "stranded" << '\n';
    } else {
        cout << ans - plan << '\n';
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