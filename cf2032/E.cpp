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

    vector<ll> operator +(vector<ll> a, vector<ll> b) {
        int sz = min(a.size(), b.size());
        vector<ll> res(sz);
        for (int i = 0; i < sz; i++) {
            res[i] = a[i] + b[i];
        }
        return res;
    }
    vector<ll> operator -(vector<ll> a, vector<ll> b) {
        int sz = min(a.size(), b.size());
        vector<ll> res(sz);
        for (int i = 0; i < sz; i++) {
            res[i] = a[i] - b[i];
        }
        return res;
    }

    void print(vector<ld> a) {
        cerr << "!!" << nl;
        for (auto x : a) cerr << x << ' ';
        cerr << nl;
    }

    void gauss(vector<vector<ld>> &a, int n, int m) // n个方程 m个变量，可能非满秩   
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
            ld coef = (ld) 1.0 / a[bg][i];
            for(int j = i; j < m; j++)  
                a[bg][j] = (a[bg][j] * coef);  
            for(int j = 0; j < n; j++)  
            {  
                if(j == bg)  
                    continue;  
                coef = a[j][i];  
                for(int k = i; k < m; k++)  
                    a[j][k] = (a[j][k] - a[bg][k] * coef);  
            }  
            ++bg;  
        }  
    }  

    void solve() {
        int n;
        cin >> n;
        vector<int> ori(n);
        for (int i = 0; i < n; i++) {
            cin >> ori[i];
        }
        if (n == 1) {
            cout << 0 << nl;
            return;
        }
        if (n == 3) {
            int mx = max({ori[0], ori[1], ori[2]});
            for (int i = 0; i < n; i++) {
                cout << mx - ori[i] << ' ';
            }
            cout << nl;
            return;
        }
        auto pre = [&](int x) {
            return (x - 1 + n) % n;
        };
        auto nxt = [&](int x) {
            return (x + 1) % n;
        };
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = ori[i] - ori[pre(i)];
        }
        vector<vector<ll>> eqs;
        eqs.pb(vector<ll>{1, 0, 0, 0});
        eqs.pb(vector<ll>{0, 1, 0, 0});
        eqs.pb(vector<ll>{0, 0, 1, 0});
        for (int i = 0; i < n; i++) {
            auto A = eqs.end()[-3];
            auto B = eqs.end()[-2];
            auto C = eqs.end()[-1];
            auto val = vector<ll>{0, 0, 0, a[i]};
            auto D = A + B - C - val;
            for (int j = 0; j < 4; j++) {
                cerr << D[j] << ' ';
            }
            cerr << nl;
            eqs.pb(D);
        }
        
        auto A = eqs.end()[-3];
        auto B = eqs.end()[-2];
        auto C = eqs.end()[-1];
        A = A - vector<ll>{1, 0, 0, 0};
        B = B - vector<ll>{0, 1, 0, 0};
        C = C - vector<ll>{0, 0, 1, 0};
        vector<vector<ld>> g;
        {
            vector<ld> tmp;
            for (int i = 0; i < 4; i++) {
                tmp.pb(A[i]);
            }
            g.pb(tmp);
        }
        {
            vector<ld> tmp;
            for (int i = 0; i < 4; i++) {
                tmp.pb(B[i]);
            }
            g.pb(tmp);
        }
        {
            vector<ld> tmp;
            for (int i = 0; i < 4; i++) {
                tmp.pb(C[i]);
            }
            g.pb(tmp);
        }
        gauss(g, 3, 4);
        print(g[0]), print(g[1]), print(g[2]);
        ll x = (ll)-g[0][3];
        ll y = (ll)-g[1][3];
        ll z = 0;
        if (x < 0) {
            ll ex = abs(x);
            x += ex, y += ex, z += ex;
        }
        if (y < 0) {
            ll ex = abs(y);
            x += ex, y += ex, z += ex;
        }
        for (int i = 2; i < n + 2; i++) {
            auto eq = eqs[i];
            ll tmp = eq[0] * x + eq[1] * y + eq[2] * z + eq[3];
            ll coef = eq[0] + eq[1] + eq[2];
            if (tmp < 0) {
                tmp = abs(tmp);
                ll ex = (tmp + coef - 1) / coef;
                x += ex, y += ex, z += ex;
            }
        }
        // cerr << x << ' ' << y << ' ' << z << nl;
        vector<ll> res(n);
        for (int i = 2; i < n + 2; i++) {
            auto eq = eqs[i];
            cout << eq[0] * x + eq[1] * y + eq[2] * z + eq[3] << ' ' ;
        }
        cout << nl;
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