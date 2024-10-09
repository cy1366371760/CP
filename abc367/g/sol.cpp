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
const int N = 2e6 + 100;
const ll inf = 1e18;
const ll mod = 998244353;

int n, m, k;

ll qpow(ll x, ll y = mod - 2) {
    ll res = 1;
    while (y) {
        if (y & 1) res = res * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return res;
}

ll inv2 = qpow(2);
void Ad(ll &x, ll y) {
    x = (x + y) % mod;
}
void Mul(ll &x, ll y) {
    x = x * y % mod;
}

void Xor(vector<ll> &a,bool inv, int len)  
{  
    ll tp;  
    for(int l=2,md=1;l<=len;l<<=1,md<<=1)  
        for(int i=0;i<len;i+=l)  
            for(int j=0;j<md;j++)  
            {  
                tp=a[i+j+md];  
                a[i+j+md]=(a[i+j]-tp+mod)%mod;  
                Ad(a[i+j],tp);  
                if(inv)Mul(a[i+j],inv2),Mul(a[i+j+md],inv2);  
            }  
}  

void solve() {
    cin >> n >> m >> k;
    int bit_num = 20;
    int len = (1 << bit_num);
    vector<ll> cnt(len);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        ++cnt[x];
    }
    if (n < m) {
        cout << 0 << '\n';
        return;
    }
    Xor(cnt, 0, len);
    // for (int i = 0; i < len; i++) {
    //     cerr << "!!" << i << ' ' << cnt[i] << '\n';
    // }
    vector f1(n + 1, vector<ll>(m, 0));
    vector f2(n + 1, vector<ll>(m, 0));
    f1[0][0] = f2[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            Ad(f1[i][j], f1[i - 1][j]);
            Ad(f1[i][(j + 1) % m], f1[i - 1][j]);
            Ad(f2[i][j], f2[i - 1][j]);
            Ad(f2[i][(j + 1) % m], mod - f2[i - 1][j]);
        }
    }
    vector<ll> dp(n + 1, 0);
    for (int k = 0; k <= n; k++) {
        for (int r = 0; r < m; r++) {
            Ad(dp[k], f1[k][r] * f2[n - k][(m - r) % m] % mod);
        }
    }
    vector<ll> res(len);
    for (int i = 0; i < len; i++) {
        int nw = cnt[i];
        int positive = (nw - (-n)) * qpow(2) % mod;
        res[i] = dp[positive];
        // cerr << "??" << i << ' ' << positive << '\n';
    }
    Xor(res, 1, len);
    ll ans = 0;
    for (int i = 0; i < len; i++) {
        // cerr << i << ' ' << res[i] << '\n';
        Ad(ans, qpow(i, k) * res[i] % mod);
    }
    cout << ans << '\n';
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