#include<bits/stdc++.h>

#define ll long long
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define eb emplace_back
#define fi first
#define sc second

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
    string s;
    cin >> n >> s;
    auto hav_1 = [&](string s) {
        for (int i = s.length() - 1; i >= 0; i--) {
            if (s[i] == '1') {
                return i + 1;
            }
        }
        return 0;
    };
    string res = "";
    int type = 0;
    while (1) {
        int need = hav_1(s);
        if (need == 0) {
            break;
        }
        for (int i = 0; i < need; i++) {
            if (s[i] == '1') {
                s[i] = '0';
            } else {
                s[i] = '1';
            }
            if (type == 0) res += 'A';
            else res += 'B';
        }
        type ^= 1;
    }
    cout << res.length() << '\n';
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
