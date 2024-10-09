ll floor_sum(ll a, ll b, ll c, ll n) { // sum i=0...n, floor((a*i + b)/c)
    if (a == 0) {  
        return (n + 1) * (b / c) % mod;  
    }  
    ll mx = (a * n + b) / c; // 0, mx - 1  
    if (mx == 0) {  
        return 0;  
    }  
    if (a >= c || b >= c) {  
        return (n * (n + 1) / 2 % mod * (a / c) % mod + (n + 1) * (b / c) % mod + floor_sum(a % c, b % c, c, n)) % mod;  
    }  
    return ((mx * (n + 1) - floor_sum(c, a + c - b - 1, a, mx - 1)) % mod + mod) % mod;
}

ll floor_sum(ll a, ll b, ll c, ll n) { // sum i=0...n, floor((a*i + b)/c)
    if (a == 0) {  
        return (n + 1) * (b / c) ;  
    }  
    ll mx = (a * n + b) / c; // 0, mx - 1  
    if (mx == 0) {  
        return 0;  
    }  
    if (a >= c || b >= c) {  
        return (n * (n + 1) / 2 * (a / c)  + (n + 1) * (b / c) + floor_sum(a % c, b % c, c, n));  
    }  
    return (mx * (n + 1) - floor_sum(c, a + c - b - 1, a, mx - 1));
}