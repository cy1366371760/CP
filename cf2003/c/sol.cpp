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
    string s;
    cin >> s;
    vector<int> cnt(30, 0);
    for (int i = 0; i < n; i++) {
        cnt[s[i] - 'a']++;   
    }
    priority_queue<pii> pq;
    for (int i = 0; i < 26; i++) {
        if (cnt[i]) pq.push(pii(cnt[i], i));
    }
    string res = "";
    while (!pq.empty()) {
        if (pq.size() == 1) {
            auto [num, c] = pq.top();
            pq.pop();
            for (int i = 0; i < num; i++) {
                res += (char)('a' + c);
            }
            break;
        }
        auto [num1, c1] = pq.top();
        pq.pop();
        auto [num2, c2] = pq.top();
        pq.pop();
        res += (char)('a' + c1);
        res += (char)('a' + c2);
        --num1, --num2;
        if (num1) pq.push(pii(num1, c1));
        if (num2) pq.push(pii(num2, c2));
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