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

ll fac[N], ifac[N];
ll qpow(ll x, ll y = mod - 2) {
	ll res = 1;
	while (y) {
		if (y & 1) res = res * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return res;
}
ll C(ll x, ll y) {
	if (x < y || y < 0) return 0;
	return fac[x] * ifac[y] % mod * ifac[x - y] % mod;
}

namespace siever  
{  
    const int N = 2e5 + 100;  
    ll n, m, B, num;  
    ll val[N], g[3][N], sum[3][N], f[3][N], pre[3][N];  
    int ps1[N], ps2[N];  
        
    int pos(ll x)  
    {  
        if(x <= B)  
            return ps1[x];  
        return ps2[n / x];  
    }  
        
    int pnum;  
    int pri[N];  
    bool np[N];
    
    void work(ll _n, ll _m)  
    {  
        n = _n;  
        m = _m;
        B = sqrt(n);  
        /*
            sum[k][i] = Prefix Sum of (pri_i ^ k)
        */
        for(int i = 2; i <= B; i++)  
        {  
            if(!np[i])  
            {  
                pri[++pnum] = i;  
                sum[0][pnum] = pnum;  
                sum[1][pnum] = sum[1][pnum - 1] + (i % 3 == 1);  
                sum[2][pnum] = sum[2][pnum - 1] + (i % 3 == 2);
            }  
            for(int j = 1; j <= pnum && i * pri[j] <= B; j++)  
            {  
                np[i * pri[j]] = 1;  
                if(i % pri[j] == 0)  
                    break;  
            }  
        }  
        /*
            Give index to Each Block of [n / d]
            Small Index -> Bigger Original Value

            g[k][i] Indicates Prefix Sum of (i ^ k)
        */
        
        auto valid_count1 = [&] (ll x) {
            return (x - 1) / 3LL;
        };
        
        auto valid_count2 = [&] (ll x) {
            return (x + 1) / 3LL;
        };

        for(ll l = 1, r; l <= n; l = r + 1)  
        {  
            ll x = n / l;  
            r = n / x;  
            val[++num] = x;  
            if(x <= B)  
                ps1[x] = num;  
            else ps2[n / x] = num;  
            g[0][num] = (x - 1 + mod) % mod;  
            g[1][num] = valid_count1(x) % mod;
            g[2][num] = valid_count2(x) % mod;
        }  
        /*
            Calculate Prefix Sum of (i ^ k) with [i is Prime]
            g[k][num] = Prefix Sum from (1 to val[num]) of (i ^ k) with [i is Prime]
        */
        for(int i = 1; i <= pnum; ++i)  
        {  
            for(int j = 1; j <= num && 1LL * pri[i] * pri[i] <= val[j]; ++j)  
            {  
                int bf = pos(val[j] / pri[i]);  
                g[0][j] = (g[0][j] - g[0][bf] + sum[0][i - 1] + mod) % mod;

                if (pri[i] % 3 == 1) {
                    g[1][j] = (g[1][j] - g[1][bf] + sum[1][i - 1] + mod) % mod;
                    g[2][j] = (g[2][j] - g[2][bf] + sum[2][i - 1] + mod) % mod;
                } else if (pri[i] % 3 == 2) {
                    g[2][j] = (g[2][j] - g[1][bf] + sum[1][i - 1] + mod) % mod;
                    g[1][j] = (g[1][j] - g[2][bf] + sum[2][i - 1] + mod) % mod;
                }

                // if (pri[i] % 3 != 2) {
                    // g[1][j] = (g[1][j] - g[1][bf] + sum[1][i - 1] + mod) % mod;
                // }
                // cerr << "??" << pri[i] << ' ' << val[j] << ' ' << g[1][j] << nl;
            }  
        }   
        /*
            Calculate the contribution of Prime Position to Final answer
            f[i] = the contribution of Prime Position to Final answer (1 to val[i])

            Calculate Pre[i] = Contribution of the 1st Prime to i'th Prime
        */
        for(int i = 1; i <= num; i++) {
            f[0][i] = m * g[0][i] % mod; 
            f[1][i] = m * (g[0][i] - g[2][i] + mod) % mod;
            // if (val[i] == 5) {
            //     cerr << "miao" << ' ' << g[0][i] << ' ' << g[2][i] << nl;
            // }
            // cerr << "!!" << i << ' ' << val[i] << ' ' << f[0][i] << ' ' << f[1][i] << nl;
        }  
        for(int i = 1; i <= pnum; i++) {
            pre[0][i] = m * sum[0][i] % mod;  
            pre[1][i] = m * (sum[0][i] - sum[2][i] + mod) % mod;
            // if (pri[i] == 3) {
            //     cerr << "GG" << sum[2][i] << nl;
            // }
            // cerr << "PP" << i << ' ' << pri[i] << ' ' << pre[0][i] << ' ' << pre[1][i] << nl;
        } 
        for(int j = pnum; j >= 1; j--)  
        {  
            for(int i = 1; i <= num; i++)  
            {  
                if(1LL * pri[j] * pri[j] > val[i])  
                    break;   
                ll tmp = pri[j], rem = (1LL + pri[j]) % 3;  
                for(int e = 1; tmp <= val[i] / pri[j]; e++, tmp *= pri[j])  
                {  
                    /*
                        s = Contribution of (Prime_{j} ^ e), C(m + e - 1, m - 1)
                        t = Contribution of (Prime_{j} ^ (e+1)), C(m + e, m - 1)
                    */
                   {
                        ll s = C(m + e - 1, m - 1) % mod;  
                        ll t = C(m + e, m - 1) % mod;  
                        (f[0][i] += (s * (f[0][pos(val[i] / tmp)] - pre[0][j] + mod) + t)) %= mod;  
                   }
                   {
                        ll nxt_rem = (rem + tmp * pri[j]) % 3;
                        ll s = (rem == 0 ? 0 : C(m + e - 1, m - 1) % mod);  
                        ll t = (nxt_rem == 0 ? 0 : C(m + e, m - 1) % mod);
                        (f[1][i] += (s * (f[1][pos(val[i] / tmp)] - pre[1][j] + mod) + t)) %= mod;
                        rem = nxt_rem;
                   }
                }  
            }  
        }  
        // 1 should be replaced by Contribution of 1
        ll all = (f[0][1] + 1) % mod;
        ll del = (f[1][1] + 1) % mod;
        // cerr << all << ' ' << del << nl;
        cout << (all - del + mod) % mod << nl;
    }  
}  


void solve() {
    ll n, m;
    cin >> n >> m;
    siever::work(n, m);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n = 1e6;
	fac[0] = 1;
	for (int i = 1; i <= n; i++) {
		fac[i] = fac[i - 1] * i % mod;
	}
	ifac[n] = qpow(fac[n]);
	for (int i = n - 1; i >= 0; i--) {
		ifac[i] = ifac[i + 1] * (i + 1) % mod;
	}
    // int tt = 1;
    // cin >> tt;
    // while(tt--)
        solve();
    return 0;
}