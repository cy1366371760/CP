void gauss(vector<vector<ll>> &a, int n, int m) // n个方程 m个变量，可能非满秩   
{  
    int bg = 0;  
    for(int i = 0; i < m - 1; i++)  
    {  
        int ps = bg;  
        while(ps < n && a[ps][i] == 0)  
            ++ps;  
        if(ps >= n)  
            continue;  
        if(ps != bg)  
            for(int j = 0; j < m; j++)  
                swap(a[ps][j], a[bg][j]);  
        ll coef = qpow(a[bg][i]);  
        for(int j = i; j < m; j++)  
            a[bg][j] = (a[bg][j] * coef) % mod;  
        for(int j = 0; j < n; j++)  
        {  
            if(j == bg)  
                continue;  
            coef = a[j][i];  
            for(int k = i; k < m; k++)  
                a[j][k] = (a[j][k] - a[bg][k] * coef % mod + mod) % mod;  
        }  
        ++bg;  
    }  
}  