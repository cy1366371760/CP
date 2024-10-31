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
const ll inf = 1e9;
const ll mod = 1e9 + 7;

ll pw2[N];

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n + 5, 0);
    vector<ll> pref(n + 5, 0);
    vector<ll> cnt2(n + 5, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        while (a[i] && a[i] % 2 == 0) {
            a[i] /= 2;
            cnt2[i]++;
        }
        cnt2[i] += cnt2[i - 1];
        pref[i] = pref[i - 1] + a[i];
    }
    vector<ll> ans(n + 2, 0);
    vector<int> stk;
    auto ask = [&](int l, int r) {
        ll cc = cnt2[r] - cnt2[l - 1];
        if (cc > 30) return ((ll)1e9 + 10);
        return (1LL << cc);
    };
    for (int i = 1; i <= n; i++) {
        int keep = stk.size();
        for (int j = 0; j < stk.size(); j++) {
            int bf = stk[j];
            if (a[bf] <= a[i] * ask(bf + 1, i)) {
                keep = j;
                break;
            }
        }
        while (stk.size() > keep) stk.pop_back();
        int who;
        if (stk.empty()) who = 0;
        else who = stk.back();
        int tmp = cnt2[i] - cnt2[who];
        ans[i] = (ans[who] + (pref[i - 1] - pref[who] + mod) % mod + a[i] * pw2[tmp] % mod) % mod;
        cout << ans[i] << ' ';
        stk.pb(i);
    }
    cout << nl;
}

signed main() {
    pw2[0] = 1;
    for (int i = 1; i < N; i++) {
        pw2[i] = pw2[i - 1] * 2LL % mod;
    }
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--)
        solve();
    return 0;
}