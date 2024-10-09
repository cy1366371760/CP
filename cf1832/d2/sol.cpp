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
    int n, qq;
    cin >> n >> qq;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(all(a));
    vector<ll> small_ans(n);
    ll mn = a[0];
    for (int i = 1; i < n; i++) {
        ++mn;
        chkmin(mn, a[i]);
        small_ans[i] = mn;
    }
    ll even_mn;
    ll even_extra = 0;
    // even
    {
        auto vals = a;
        for (int i = 0; i < n; i++) {
            vals[i] += n - i;
        }
        sort(all(vals));
        even_mn = vals[0];
        for (auto &x : vals) {
            even_extra += x - even_mn;
        }
    }
    ll odd_mn;
    ll odd_extra[2];
    ll odd_stable;
    // odd
    {
        auto vals = a;
        odd_stable = vals[n - 1];
        for (int i = 0; i < n - 1; i++) {
            vals[i] += n + 1 - i;
        }
        sort(all(vals));
        odd_mn = vals[0];
        odd_extra[0] = odd_extra[1] = 0;
        for (auto &x : vals) {
            odd_extra[0] += x - odd_mn;
            odd_extra[1] += x - odd_stable;
        }
    }
    while (qq--) {
        ll k;
        cin >> k;
        if (k < n) {
            cout << small_ans[k] << ' ';
            continue;
        }
        ll cur_mn;
        ll extra;
        ll del;
        if ((k - n) & 1) {
            cur_mn = odd_mn + (k - (n + 1));
            if (cur_mn > odd_stable) {
                cur_mn = odd_stable;
                extra = odd_extra[1] + 1LL * (n - 1) * (k - (n + 1));
            } else {
                extra = odd_extra[0] - (k - (n + 1));
            }
            del = (k - n + 1) / 2;
        } else {
            cur_mn = even_mn + (k - n);
            extra = even_extra;
            del = (k - n) / 2;
        }
        ll tmp = min(del, extra);
        del -= tmp;
        if (del) {
            cur_mn -= del / n;
            if (del % n) --cur_mn;
        }
        cout << cur_mn << ' ';
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