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
#define pll pair<ll, ll>
#define double long double
//#define int long long
using namespace std;

#ifdef LOCAL
void debug_out(){cerr << endl;}
template<typename Head, typename... Tail>
void debug_out(Head H, Tail... T)
{
	cerr << " " << to_string(H);
	debug_out(T...);
}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

const int N = 1e6 + 100;
const int inf = 1e9;
//const ll inf = 1e18;
const ll mod = 998244353;//1e9 + 7;

ll qpow(ll x, ll y = mod - 2) {
	ll res = 1;
	while (y) {
		if (y & 1) {
			res = res * x % mod;
		}
		x = x * x % mod;
		y >>= 1;
	}
	return res;
}

int n;
int a[N];
template<size_t size>
struct SuffixArray {
    bool type[size << 1];
    int bucket[size], bucket1[size];
    int sa[size], rk[size], ht[size];
    inline bool isLMS(const int i, const bool *type) { return i > 0 && type[i] && !type[i - 1]; }
    template<class T>
    inline void inducedSort(T s, int *sa, const int len, const int sigma, const int bucketSize, bool *type, int *bucket, int *cntbuf, int *p) {
        memset(bucket, 0, sizeof(int) * sigma);
        memset(sa, -1, sizeof(int) * len);
        for (register int i = 0; i < len; i++) bucket[s[i]]++;
        cntbuf[0] = bucket[0];
        for (register int i = 1; i < sigma; i++) cntbuf[i] = cntbuf[i - 1] + bucket[i];
        for (register int i = bucketSize - 1; i >= 0; i--) sa[--cntbuf[s[p[i]]]] = p[i];
        for (register int i = 1; i < sigma; i++) cntbuf[i] = cntbuf[i - 1] + bucket[i - 1];
        for (register int i = 0; i < len; i++) if (sa[i] > 0 && !type[sa[i] - 1]) sa[cntbuf[s[sa[i] - 1]]++] = sa[i] - 1;
        cntbuf[0] = bucket[0];
        for (register int i = 1; i < sigma; i++) cntbuf[i] = cntbuf[i - 1] + bucket[i];
        for (register int i = len - 1; i >= 0; i--) if (sa[i] > 0 && type[sa[i] - 1]) sa[--cntbuf[s[sa[i] - 1]]] = sa[i] - 1;
    }
    template<typename T>
    inline void sais(T s, int *sa, int len, bool *type, int *bucket, int *bucket1, int sigma) {
        int i, j, bucketSize = 0, cnt = 0, p = -1, x, *cntbuf = bucket + sigma;
        type[len - 1] = 1;
        for (i = len - 2; i >= 0; i--) type[i] = s[i] < s[i + 1] || (s[i] == s[i + 1] && type[i + 1]);
        for (i = 1; i < len; i++) if (type[i] && !type[i - 1]) bucket1[bucketSize++] = i;
        inducedSort(s, sa, len, sigma, bucketSize, type, bucket, cntbuf, bucket1);
        for (i = bucketSize = 0; i < len; i++) if (isLMS(sa[i], type)) sa[bucketSize++] = sa[i];
        for (i = bucketSize; i < len; i++) sa[i] = -1;
        for (i = 0; i < bucketSize; i++) {
            x = sa[i];
            for (j = 0; j < len; j++) {
                if (p == -1 || s[x + j] != s[p + j] || type[x + j] != type[p + j]) { cnt++, p = x; break; }
                else if (j > 0 && (isLMS(x + j, type) || isLMS(p + j, type))) break;
            }
            x = (~x & 1 ? x >> 1 : x - 1 >> 1), sa[bucketSize + x] = cnt - 1;
        }
        for (i = j = len - 1; i >= bucketSize; i--) if (sa[i] >= 0) sa[j--] = sa[i];
        int *s1 = sa + len - bucketSize, *bucket2 = bucket1 + bucketSize;
        if (cnt < bucketSize) sais(s1, sa, bucketSize, type + len, bucket, bucket1 + bucketSize, cnt);
        else for (i = 0; i < bucketSize; i++) sa[s1[i]] = i;
        for (i = 0; i < bucketSize; i++) bucket2[i] = bucket1[sa[i]];
        inducedSort(s, sa, len, sigma, bucketSize, type, bucket, cntbuf, bucket2);
    }
    template<class T>
    inline void getHeight(T s, const int len, const int *sa) {
        for (int i = 0, k = 0; i < len; i++) {
            if (rk[i] == 0) k = 0;
            else {
                if (k > 0) k--;
                int j = sa[rk[i] - 1];
                while (i + k < len && j + k < len && s[i + k] == s[j + k]) k++;
            }
            ht[rk[i]] = k;
        }
    }
    template<class T>
    inline void init(T s, const int len, const int sigma) {
        sais(s, sa, len, type, bucket, bucket1, sigma);
        for (register int i = 1; i < len; i++) rk[sa[i]] = i;
        getHeight(s, len, sa);
    }
};

SuffixArray<N> sf;

string s;

void sol()
{
	cin >> s;
	int n = s.length();
	sf.init(s, n + 1, 256);
	for (int i = 1; i <= n; i++) { // sa数组下标从1开始，rk从0开始，值域均[0,n-1]
		cout << sf.sa[i] + 1 << ' ';
	}
	cout << '\n';
	for (int i = 0; i < n; i++) {
		cout << sf.rk[i] << ' ';
	}
	cout << '\n';
	for (int i = 2; i <= n; i++) { // lcp(sa[i], sa[i - 1])
		cout << sf.ht[i] << ' ';
	}vector<vector<int>> mn(21, vector<int>(n + 1, 0));
	vector<int> lg(n + 1, 0);
	lg[1] = 0;
	for (int i = 2; i <= n; i++) {
		mn[0][i] = sf.ht[i];
		lg[i] = lg[i >> 1] + 1;
	}
	for (int k = 1; k <= 20; k++) {
		int l = 1 << k, md = l >> 1;
		for (int i = l + 1; i <= n; i++) {
			mn[k][i] = min(mn[k - 1][i], mn[k - 1][i - md]);
		}
	}
//	vector<vector<int>> mn_rnk(21, vector<int>(n + 1, 0));
//	for (int i = 0; i < n; i++) {
//		mn_rnk[0][i] = i;
//	}
//	for (int k = 1; k <= 20; k++) {
//		int l = 1 << k, md = l >> 1;
//		for (int i = 0; i + l - 1 < n; i++) {
//			int lhs = mn_rnk[k - 1][i];
//			int rhs = mn_rnk[k - 1][i + md];
//			if (sf.rk[lhs] < sf.rk[rhs]) {
//				mn_rnk[k][i] = lhs;
//			} else mn_rnk[k][i] = rhs;
//		}
//	}
	auto lcp = [&](int i, int j) {
		if (i == j) {
			return n - i;
		}
		i = sf.rk[i], j = sf.rk[j];
		if (i > j) swap(i, j);
		++i;
		int l = j - i + 1;
		int k = lg[l];
		return min(mn[k][j], mn[k][i + (1 << k) - 1]);
	};
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
//	int tt;
//	cin >> tt;
//	while(tt--)
		sol();
}
