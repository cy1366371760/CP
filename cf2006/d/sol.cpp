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
    int n, qq, k;
    cin >> n >> qq >> k;
    int B = 1;
    while ((B + 1) * (B + 1) <= k) ++B;
    int sz = sqrt(n);
    vector <int> a(n + 5, 0);
    vector ocr(sz + 5, vector<int>(B + 1, 0));
    vector need(sz + 5, vector<int>(B + 1, 0));
    int idx = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        a[i] = x;
        if ((i - 1) % sz == 0) {
            ++idx;
            ocr[idx] = ocr[idx - 1];
            need[idx] = need[idx - 1];
        }
        if (x <= B) {
            ++ocr[idx][x];
        } else {
            assert(k / x >= 1 && k / x <= B);
            ++need[idx][k / x];
        }
    }
    auto get_ocr = [&](int i) {
        int bel = i / sz;
        auto res = ocr[bel];
        int bg = bel * sz + 1;
        for (int j = bg; j <= i; j++) {
            int x = a[j];
            if (x <= B) ++res[x];
        }
        return res;
    };
    auto get_need = [&](int i) {
        int bel = i / sz;
        auto res = need[bel];
        int bg = bel * sz + 1;
        for (int j = bg; j <= i; j++) {
            int x = a[j];
            if (x > B) ++res[k / x];
        }
        return res;
    };
    while (qq--) {
        int l, r;
        cin >> l >> r;
        auto hav = get_ocr(r);
        auto ned = get_need(r);
        auto hav_bf = get_ocr(l - 1);
        auto ned_bf = get_need(l - 1);
        for (int i = 1; i <= B; i++) {
            hav[i] -= hav_bf[i];
            ned[i] -= ned_bf[i];
        }
        
    }
    cout << '\n';
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