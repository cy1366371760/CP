#include <algorithm>
#include <cstdio>
#include <map>
#include <vector>
using namespace std;
typedef long long ll;

constexpr int MOD = 998'244'353;
constexpr int INF = 998'244'353;

bool chmin(int &a, int b) {
	if (b < a) {
		a = b;
		return true;
	}
	return false;
}

bool chmax(int &a, int b) {
	if (b > a) {
		a = b;
		return true;
	}
	return false;
}

ll modinv(ll a, ll m) {
	ll b = m, u = 1, v = 0;
	while (b) {
		ll t = a / b;
		a -= t * b;
		swap(a, b);
		u -= t * v;
		swap(u, v);
	}
	u %= m;
	if (u < 0) u += m;
	return u;
}

int inv_2(int N) {
	ll dep = 1;
	ll pow = 499'122'177;
	while (N) {
		if (N & 1) {
			dep *= pow;
			dep %= MOD;
		}
		pow *= pow;
		pow %= MOD;
		N /= 2;
	}
	return (int)dep;
}

int exp_2(int N) {
	ll dep = 1;
	ll pow = 2;
	while (N) {
		if (N & 1) {
			dep *= pow;
			dep %= MOD;
		}
		pow *= pow;
		pow %= MOD;
		N /= 2;
	}
	return (int)dep;
}

int main() {
	int N, H;
	scanf("%d%d", &N, &H);
	int X[N];
	for (int i = 0; i < N; i++) scanf("%d", X + i);
	pair<int, int> X_id[N];
	for (int i = 0; i < N; i++) X_id[i] = {X[i], i};
	sort(X_id, X_id + N);
	vector<vector<int>> con;
	vector<int> tmp(1, X_id[0].second);
	for (int i = 1; i < N; i++) {
		if (X_id[i].first > X_id[i - 1].first + H) {
			con.push_back(tmp);
			tmp.clear();
		}
		tmp.push_back(X_id[i].second);
	}
	con.push_back(tmp);
	vector<map<int, ll>> anss;
	int init = -1;
	ll prob_init = exp_2(N);
	map<int, ll> ratio;
	for (vector<int> &vec : con) {
		int dep[vec.size() + 1];
		fill(dep, dep + vec.size() + 1, 0);
		int lis[vec.size() + 1];
		fill(lis, lis + vec.size(), INF);
		lis[0] = -1;
		int d = 0;
		for (unsigned i = 0; i < vec.size(); i++) {
			while (lis[d] > vec[i]) d--;
			lis[++d] = vec[i];
			dep[i + 1] += d;
		}
		fill(lis, lis + vec.size(), INF);
		lis[0] = -1;
		d = 0;
		for (int i = vec.size() - 1; i >= 0; i--) {
			while (lis[d] > vec[i]) d--;
			lis[++d] = vec[i];
			dep[i] += d;
		}
		map<int, ll> prob;
		int sub_min = N;
		prob[vec[0]] += inv_2(dep[0]);
		prob[vec[0]] %= MOD;
		prob[vec[vec.size() - 1]] += inv_2(dep[vec.size()]);
		prob[vec[vec.size() - 1]] %= MOD;
		for (unsigned i = 1; i < vec.size(); i++) {
			prob[max(vec[i - 1], vec[i])] += inv_2(dep[i]);
			prob[max(vec[i - 1], vec[i])] %= MOD;
		}
		int sum = 0;
		bool f = true;
		for (auto [k, v] : prob) {
			int sum_old = sum;
			sum += v;
			sum %= MOD;
			if (sum && f) {
				chmax(init, k);
				prob_init *= sum;
				prob_init %= MOD;
				f = false;
			} else {
				ratio[k] = (sum * modinv(sum_old, MOD)) % MOD;
			}
		}
		anss.push_back(prob);
	}
	prob_init = exp_2(N);
	for (auto prob : anss) {
		int sum = 0;
		bool f = true;
		for (auto [k, v] : prob) {
			if (f && (k > init)) {
				prob_init *= sum;
				prob_init %= MOD;
				f = false;
			}
			sum += v;
			sum %= MOD;
		}
		if (f) {
			prob_init *= sum;
			prob_init %= MOD;
		}
	}
	for (int i = 0; i < init; i++) {
		printf("0 ");
	}
	ll prob = prob_init;
	printf("%lld", prob);
	for (int i = init + 1; i < N; i++) {
		if (ratio[i]) {
			printf(" %lld", (prob * (ratio[i] - 1)) % MOD);
			prob *= ratio[i];
			prob %= MOD;
		} else {
			printf(" 0");
		}
	}
	printf("\n");
	return 0;
}
