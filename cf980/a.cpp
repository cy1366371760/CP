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
    int n;
    cin >> n;
    vector<pii> vals(n);
    vector<int> buk;
    for (int i = 0; i < n; i++) {
        cin >> vals[i].fi >> vals[i].sc;
        buk.pb(vals[i].fi);
        buk.pb(vals[i].sc);
    }
    buk.pb((int)-(1e9 + 100));
    sort(all(buk));
    buk.erase(unique(all(buk)), buk.end());
    vector<int> cnt(2 * n + 100, 0);
    for (int i = 0; i < n; i++) {
        vals[i].fi = lower_bound(all(buk), vals[i].fi) - buk.begin();
        vals[i].sc = lower_bound(all(buk), vals[i].sc) - buk.begin();
        cnt[vals[i].fi]++;
        cnt[vals[i].sc]++;
    }
    for (int i = 1; i < cnt.size(); i++) cnt[i] += cnt[i - 1];
    sort(all(vals), [&](auto x, auto y){
        return cnt[x.fi - 1] + cnt[x.sc - 1] < cnt[y.fi - 1] + cnt[y.sc - 1];
    });
    for (auto [x, y] : vals) cout << buk[x] << ' ' << buk[y] << ' ';
    cout << nl;
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