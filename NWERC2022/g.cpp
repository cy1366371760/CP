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

mt19937 rng(time(0));

void solve() {
    int las;
    cin >> las;
    auto out = [&](int x) {
        cout << "! " << x << endl;
        exit(0);
    };
    auto rand_string = [&](int len) -> vector<int> {
        vector<int> s;
        for (int i = 1; i <= len; i++) {
            if (rng() & 1) s.pb(0);
            else s.pb(1);
        }
        return s;
    };
    auto flip = [&]() {
        cout << "? flip" << endl;
        cin >> las;
    };
    auto right = [&]() {
        cout << "? right" << endl;
        cin >> las;
    };
    auto draw = [&](vector<int> cur) {
        for (int i = 0; i < cur.size(); i++) {
            if (las != cur[i]) flip();
            right();
        }
    };
    auto match = [&](vector<int> cur) {
        for (int i = 0; i < cur.size(); i++) {
            if (las != cur[i]) return 0;
            right();
        }
        return 1;
    };
    auto chk = [&](int x) -> bool {
        auto pat = rand_string(x);
        draw(pat);
        return match(pat);
    };
    for (int i = 3; i < 20; i++) {
        int tim = (20 + i - 1) / i;
        bool flg = 1;
        while (tim--) {
            flg &= chk(i);
            if (!flg) break;
        }
        if (flg) out(i);
    }
    {
        int tim = 2;
        vector<int> may;
        while (tim--) {
            auto pat = rand_string(20);
            draw(pat);
            deque<int> need(pat.begin(), pat.end());
            deque<int> cur;
            int res = 0;
            for (int i = 0; ; i++) {
                if (cur == need) {
                    res = i;
                    break;
                }
                if (cur.size() == 20) cur.pop_front();
                cur.pb(las);
                right();
            }
            may.pb(res);
        }
        out(*max_element(all(may)));
    }

    // int res = 0;
    // for (int i = 3; i < 10; i++) {
    //     res += (20 + i - 1) / i * (3 * i);
    // }
    // cerr << res << nl;
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