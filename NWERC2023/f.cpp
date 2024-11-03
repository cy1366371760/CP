#include<bits/stdc++.h>

#define nl '\n'
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define eb emplace_back
#define fi first
#define sc second
typedef __int128 ll;
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

string a, b;
ll c, d;


inline bool lz(int bm) {
    int i = __builtin_ctz(bm);
    // if (bm == 0b010) cerr << i << nl;
    return a[i] == '0';
}


string to_string(ll val) {
    if (val == 0) return "0";
    string res = "";
    while (val) {
        res += (char)('0' + (val % 10));
        val /= 10;
    }
    reverse(all(res));
    return res;
}

inline ll getnum(int bm, const string& s) {
    ll ans = 0;
    for (int i=0;i<s.size();i++)  if ((bm>>i)&1) {
        ans*=10;
        ans+=s[i]-'0';
    }
    return ans;
}

inline bool poss(const string& bs) {
    // substring
    int cur = 0;
    for(int i=0;i<bs.size();i++) {
        while(cur < b.size() && b[cur] != bs[i]) cur++;
        if (cur >= b.size()) return 0;
        cur++;
    }
    return 1;
}

inline bool posnum(const string& bs, int bm) {
    string aa;
    for (int i=0;i<a.size();i++) if (((bm >> i) & 1)==0) {
        aa.pb(a[i]);
    }
    string bb;


    // if (bm == 0b110) {
    //     cerr << bs << " " << b << nl;

    // }

    int cur = 0;
    for(int i=0;i<bs.size();i++) {
        while(cur < b.size() && b[cur] != bs[i]) {
            bb.pb(b[cur]);
            cur++;
        }
        cur++;
    }

    for (;cur<b.size();cur++) bb.pb(b[cur]);

    sort(all(aa));
    sort(all(bb));

    // if (bm == 0b110) {

    //     // cerr <<aa << " " << bb << nl;
    //     // cerr << getnum(bm, a) << nl;
    //     // cerr << ds << nl;
    //     // cerr << poss(ds) << nl;
    //     // cerr << posnum(ds, bm) << nl;
    // }

    
    return aa == bb;
}

inline bool pos(int bm) {
    if (lz(bm)) return 0;
    ll num = getnum(bm, a);
    if (num % c != 0) return 0;
    ll den = (num / c) * d;
    string ds = to_string(den);

    if (bm == 0b110) {

        // cerr <<aa << " " << bb << nl;
        // cerr << getnum(bm, a) << nl;
        // cerr << ds << nl;
        // cerr << poss(ds) << nl;
        // cerr << posnum(ds, bm) << nl;
    }

    return poss(ds) && posnum(ds, bm);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    long long cc, dd;
    cin >> a >> b >> cc >> dd;
    c = cc, d = dd;
    // cin >> a >> b >> c >> d;
    ll g = __gcd(c, d);
    c/=g;d/=g;

    // cerr << getnum(0b1110, "1234") << nl;

    for (int bm=1;bm<(1<<a.size());bm++) {
        // cerr << getnum(bm, a) << nl;
        if (pos(bm)) {
            ll num = getnum(bm, a);
            ll den = (num / c) * d;
            cout << "possible" << nl;
            cout << (long long)num << " " << (long long)den << nl;
            return 0;
        }
    }

    cout << "impossible";


    cout << nl;

    return 0;
}