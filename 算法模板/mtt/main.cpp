#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define sc second
#define pb push_back
#define ll long long
#define trav(v,x) for(auto v:x)
#define all(x) (x).begin(), (x).end()
#define VI vector<int>
#define VLL vector<ll>
#define db double
using namespace std;
const int N = 1e6 + 100;
const int M = 32767;
const db pi = acos(-1);
const ll mod = 998244352;

struct cp{
    db r, i;
    cp(double r = 0, double i = 0) : r(r), i(i){}
    cp operator * (const cp &a) {return cp(r * a.r - i * a.i, r * a.i + i * a.r);}
    cp operator + (const cp &a) {return cp(r + a.r, i + a.i);}
    cp operator - (const cp &a) {return cp(r - a.r, i - a.i);}
}w[N], A[N], B[N], AA[N], BB[N];

int len, cc, wh[N];

cp conj(cp a)
{return cp(a.r, -a.i);}

void fft(cp *a, bool inv)
{
    cp tmp;
    for(int i = 0; i < len; i++)
        if(i < wh[i])swap(a[i], a[wh[i]]);
    for(int l = 2; l <= len; l <<= 1)
    {
        int mid = l >> 1;
        for(int i = 0; i < len; i += l)
        {
            for(int j = 0; j < mid; j++)
            {
                tmp = a[i + j + mid] * (inv ? w[len - len / l * j] : w[len / l * j]);
                a[i + j + mid] = a[i + j] - tmp;
                a[i + j] = a[i + j] + tmp;
            }
        }
    }
}

VI mul(VI &a, VI &b) // mtt with M = 32767
{
    VI res;
    len = 1, cc = 0;
    while(len < a.size() + b.size())
        len <<= 1, ++cc;
    for(int i = 1; i <= len; i++)
        wh[i] = (wh[i >> 1] >> 1) | ((i & 1) << (cc - 1));
    for(int i = 0; i <= len; i++)
        w[i] = cp(cos(2.0 * pi * i / len), sin(2.0 * pi * i / len));
    int sz = a.size() + b.size() - 1;
    a.resize(len), b.resize(len);
    for(int i = 0; i < len; i++)
    {
        A[i] = cp(a[i] / M, a[i] % M);
        B[i] = cp(b[i] / M, b[i] % M);
    }
    fft(A, 0), fft(B, 0);
    for(int i = 0; i < len; i++)
    {
        cp aa, bb, cc, dd;
        int j = (len - i) % len;
        aa = (A[i] + conj(A[j])) * cp(0.5, 0);
        bb = (A[i] - conj(A[j])) * cp(0, -0.5);
        cc = (B[i] + conj(B[j])) * cp(0.5, 0);
        dd = (B[i] - conj(B[j])) * cp(0, -0.5);
        AA[i] = aa * cc + aa * dd * cp(0, 1);
        BB[i] = bb * dd + bb * cc * cp(0, 1);
    }
    fft(AA, 1), fft(BB, 1);
    res.resize(sz);
    for(int i = 0; i < sz; i++)
    {
        ll ac, ad, bc, bd;
        ac = (ll)(AA[i].r / len + 0.5) % mod;
        ad = (ll)(AA[i].i / len + 0.5) % mod;
        bd = (ll)(BB[i].r / len + 0.5) % mod;
        bc = (ll)(BB[i].i / len + 0.5) % mod;
        res[i] = (ac * M * M + (ad + bc) * M + bd) % mod;
    }
    return res;
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
    return 0;
}
