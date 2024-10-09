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
    int d = 0;
    auto mov = [&](vector<int> cur) {
        cout << "next ";
        for (int x : cur) {
            cout << x << ' ';
        }
        cout << endl;
        vector sam(10, vector<bool>(10, 0));
        int num;
        cin >> num;
        for (int i = 0; i < num; i++) {
            string s;
            cin >> s;
            for (int j = 0; j < s.length(); j++) {
                for (int k = j + 1; k < s.length(); k++) {
                    int x = s[j] - '0';
                    int y = s[k] - '0';
                    sam[x][y] = sam[y][x] = 1;
                }
            }
        }
        return sam;
    };
    while (1) {
        mov({0, 1});
        auto sam = mov({0});
        ++d;
        if (sam[0][1]) {
            break;
        }
    }
    int c = 1;
    auto sam = mov({0});
    while (!sam[0][1]) {
        ++c;
        sam = mov({0});
    }
    int t = d - (c - 1);
    int r = c - 1;
    for (int i = 0; i < t; i++) mov({2, 3, 4, 5, 6, 7, 8, 9});
    sam = mov({0, 1});
    auto ok = [&](auto sam) {
        for (int i = 1; i < 10; i++) {
            if (!sam[0][i]) return false;
        }
        return true;
    };
    while (!ok(sam)) {
        sam = mov({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    }
    cout << "done" << endl;
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