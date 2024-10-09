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
    auto ask = [&](int x, string s) {
        cout << "? " << x << ' ' << s << endl;
        int re;
        cin >> re;
        return re;
    };
    string all = "";
    for (int i = 0; i < n; i++) {
        all += '1';
    }
    vector<pii> order(n);
    for (int i = 1; i <= n; i++) {
        string nw = all;
        nw[i - 1] = '0';
        int val = ask(i, nw);
        order[i - 1] = pii(val, i);
    }
    sort(all(order));
    reverse(all(order));
    vector<int> ok;
    ok.pb(order[0].sc);
    for (int i = 1; i < n; i++) {
        auto [_, idx] = order[i];
        string s = "";
        for (int j = 0; j < n; j++) s += '0';
        for (int x : ok) {
            s[x - 1] = '1';
        }
        int re = ask(idx, s);
        if (re) {
            ok.clear();
            for (int j = 0; j <= i; j++) {
                ok.pb(order[j].sc);
            }
        }
    }
    string res = "";
    for (int i = 0; i < n; i++) res += '0';
    for (int x : ok) res[x - 1] = '1';
    cout << "! " << res << endl;
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