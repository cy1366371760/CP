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
typedef vector<ll> vi;
const int N = 1e6 + 100;
const ll inf = 1e18;
const ll mod = 998244353;
const ld eps = (ld)1e-20;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n;
    cin >> n;
    vi arr(n);
    for (int i=0;i<n;i++) cin >> arr[i];

    if (n == 1) {
        cout << arr[0] << nl;
        return 0;
    }

    sort(all(arr));
    int numones = 0;
    for (int i=0;i<n;i++) if (arr[i] == 1) numones++; else break;

    vector<string> ans;

    for (int i=0;i<numones/2;i++) {
        ans.pb("(1+1)");
    }

    int st = numones;

    if (numones % 2) {
        if (ans.size()) {
            ans.pop_back();
            ans.pb("(1+1+1)");
        }
        else {
            ans.pb("(1+" + to_string(arr[numones]) + ")");
            st = numones + 1;
        }
    }

    for (int i=st;i<n;i++) ans.pb(to_string(arr[i]));


    for (int i=0;i<ans.size();i++) {
        cout << ans[i];
        if (i < ans.size()-1) cout << "*";
    }

    cout << nl;

    return 0;
}