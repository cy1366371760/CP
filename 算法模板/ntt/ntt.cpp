
ll qpow(ll x, ll y = mod - 2)
{
	ll res = 1;
	while(y)
	{
		if(y & 1)
			res = res * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return res;
}

namespace Poly
{
	int wh[N], len, cc;
	void ntt(VLL &a, bool inv)
	{
		for(int i = 0; i < len; i++)
			if(i < wh[i])swap(a[i], a[wh[i]]);
		for(int l = 2; l <= len; l <<= 1)
		{
			int md = l >> 1;
			ll tp = qpow(3, (mod - 1) / l);
			for(int i = 0; i < len; i += l)
			{
				ll mo = 1;
				for(int j = 0; j < md; j++, mo = mo * tp % mod)
				{
					ll ha = mo * a[i + j + md] % mod;
					a[i + j + md] = (a[i + j] - ha + mod) % mod;
					a[i + j] = (a[i + j] + ha) % mod;
				}
			}
		}
		if(inv)
		{
			ll tmp = qpow(len);
			for(int i = 1; i < len / 2; i++)
				swap(a[i], a[len - i]);
			for(int i = 0; i < len; i++)
				a[i] = a[i] * tmp % mod;
		}
	}
	VLL mul(VLL x, VLL y)
	{
		cc = 0, len = 1;
		while(len < x.size() + y.size())
			++cc, len <<= 1;
		for(int i = 1; i < len; i++)
		{
			wh[i] = (wh[i >> 1] >> 1) | ((i & 1) << (cc - 1));
		}
		int bf = x.size() + y.size() - 1;
		x.resize(len);
		y.resize(len);
		ntt(x, 0), ntt(y, 0);
		for(int i = 0; i < len; i++)
			x[i] = x[i] * y[i] % mod;
		ntt(x, 1);
		x.resize(bf);
		return x;
	}
}
