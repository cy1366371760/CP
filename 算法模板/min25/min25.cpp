namespace siever {  
    const int N = 2e5 + 100;  
    ll n, B, num;  
    ll val[N], g[2][N], sum[2][N], f[N], pre[N];  
    int ps1[N], ps2[N];      
    int pos(ll x) {  
        if(x <= B)  
            return ps1[x];  
        return ps2[n / x];  
    }  
    int pnum;  
    int pri[N];  
    bool np[N];
    void work(ll _n) {  
        n = _n;  
        B = sqrt(n);  
        /*
            sum[k][i] = Prefix Sum of [pri_i ^ k]
        */
        for (int i = 2; i <= B; i++) {  
            if(!np[i]) {  
                pri[++pnum] = i;  
                sum[0][pnum] = pnum;  
                sum[1][pnum] = (sum[1][pnum - 1] + i) % mod;  
            }  
            for(int j = 1; j <= pnum && i * pri[j] <= B; j++) {  
                np[i * pri[j]] = 1;  
                if(i % pri[j] == 0)  
                    break;  
            }  
        }  
        /*
            Give index to Each Block of [n / d]
            Small Index -> Bigger Original Value

            g[k][i] Indicates Prefix Sum of (i ^ k), Notice it Starts From Index 2nd
        */
        for (ll l = 1, r; l <= n; l = r + 1) {  
            ll x = n / l;  
            r = n / x;  
            val[++num] = x;  
            if(x <= B)  
                ps1[x] = num;  
            else ps2[n / x] = num;  
            x %= mod;  
            g[0][num] = (x - 1 + mod) % mod;  
            g[1][num] = (x - 1 + mod) % mod * (x + 2) / 2 % mod;
        }  
        /*
            Calculate Prefix Sum of (i ^ k) with [i is Prime]
            g[k][num] = Prefix Sum from (1 to val[num]) of (i ^ k) with [i is Prime]
        */
        for(int i = 1; i <= pnum; ++i) {  
            for(int j = 1; j <= num && 1LL * pri[i] * pri[i] <= val[j]; ++j) {  
                int bf = pos(val[j] / pri[i]);  
                g[0][j] = (g[0][j] - g[0][bf] + sum[0][i - 1] + mod) % mod;  
                g[1][j] = (g[1][j] - pri[i] * (g[1][bf] - sum[1][i - 1] + mod) % mod + mod) % mod;  
            }  
        }  
        /*
            Calculate the contribution of Prime Position to Final answer
            f[i] = the contribution of Prime Position to Final answer in [1 to val[i]]

            Calculate Pre[i] = Contribution of the [1st Prime to i'th Prime]
        */
        for(int i = 1; i <= num; i++)  
            f[i] = (g[1][i] - g[0][i] + mod) % mod;  
        for(int i = 1; i <= pnum; i++)  
            pre[i] = (sum[1][i] - sum[0][i] + mod) % mod;  
        for(int j = pnum; j >= 1; j--) {  
            for(int i = 1; i <= num; i++) {  
                if(1LL * pri[j] * pri[j] > val[i])  
                    break;   
                ll tmp = pri[j];  
                for(int e = 1; tmp <= val[i] / pri[j]; e++, tmp *= pri[j]) {  
                    /*
                        s = Contribution of [Prime_{j} ^ e]
                        t = Contribution of [Prime_{j} ^ (e+1)]
                    */
                    ll s = (tmp - tmp / pri[j]) % mod;  
                    ll t = (tmp * pri[j] - tmp) % mod;  
                    (f[i] += (s * (f[pos(val[i] / tmp)] - pre[j] + mod) + t)) %= mod;  
                }  
            }  
        }  
        // 1 should be replaced by Contribution of index 1
        cout << (f[1] + 1) % mod;  
    }  
}  