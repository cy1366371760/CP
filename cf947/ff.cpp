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

int n;
int len, U;
ll vt[N], a[N], b[N], ans[N];

void Dw(ll &x, ll b) {x = x - b;}
void Ad(ll &x, ll b) {x = x + b;}

void And(ll *a,bool inv, vector<int> may)  
{  
    for (int bit = n - 1; bit >= 0; bit--) {
        for (int i = may.size() - 1; i >= 0; i--) {
            int x = may[i];
            if (x >> bit & 1) {
                Ad(a[x ^ (1 << bit)], a[x]);
            }
        }
    }
}  
    
void Or(ll *a,bool inv)  
{  
    for(int l=2,md=1;l<=len;l<<=1,md<<=1)  
        for(int i=0;i<len;i+=l)  
            for(int j=0;j<md;j++)  
                inv?Dw(a[i+j+md],a[i+j]):Ad(a[i+j+md],a[i+j]);  
}  

ll C[30][30];

void solve() {
    for (int i = 0; i < 30; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        }
    }
    cin >> n;
    len = 1 << n;
    U = len - 1;
    for (int i = 1; i < len; i++) {
        cin >> vt[i];
    }
    for (int v = 0; v <= n; v++) {
        for (int i = 0; i < len; i++) b[i] = 0;
        vector<int> may;
        for (int i = 0; i < len; i++) {
            int tmp = __builtin_popcount(i);
            if (tmp >= v) {
                may.pb(i);
                a[i] = (((tmp - v) & 1) ? -1 : 1);
                a[i] = a[i] * C[tmp][v];
                if (i > 0 && (vt[i] >> v & 1)) {
                    b[i]++;
                }
            } else {
                a[i] = 0;
            }
        }
        And(b, 0, may);
        for (int i = 0; i < len; i++) {
            b[i] *= a[i];
        }
        for (int i = 0; i < len; i++) {
            ans[i] += b[i];
        }
    }
    Or(ans, 0);
    vector<int> res;
    for (int i = 0; i < len; i++) {
        if (ans[i] == U) res.pb(i);
    }
    cout << res.size() << '\n';
    for (int i : res) {
        cout << i << '\n';
    }
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
