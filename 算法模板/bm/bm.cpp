#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2005;
const double eps = 1e-8;
template <typename T> void read(T &x) {
	x = 0; int f = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
	for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
	x *= f;
}
int cnt, fail[MAXN];
double val[MAXN], delta[MAXN];
vector <double> ans[MAXN];
int main() {
	int n; read(n);
	for (int i = 1; i <= n; i++)
		scanf("%lf", &val[i]);
	for (int i = 1; i <= n; i++) {
		double tmp = val[i];
		for (unsigned j = 0; j < ans[cnt].size(); j++)
			tmp -= ans[cnt][j] * val[i - j - 1];
		delta[i] = tmp;
		if (fabs(tmp) <= eps) continue;
		fail[cnt] = i;
		if (cnt == 0) {
			ans[++cnt].resize(i);
			continue;
		}
		double mul = delta[i] / delta[fail[cnt - 1]];
		cnt++; ans[cnt].resize(i - fail[cnt - 2] - 1);
		ans[cnt].push_back(mul);
		for (unsigned j = 0; j < ans[cnt - 2].size(); j++)
			ans[cnt].push_back(ans[cnt - 2][j] * -mul);
		if (ans[cnt].size() < ans[cnt - 1].size()) ans[cnt].resize(ans[cnt - 1].size());
		for (unsigned j = 0; j < ans[cnt - 1].size(); j++)
			ans[cnt][j] += ans[cnt - 1][j];
	}
	for (unsigned i = 0; i < ans[cnt].size(); i++)
		cout << ans[cnt][i] << ' ';
	return 0;
}
