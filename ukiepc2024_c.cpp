#include <bits/stdc++.h>
using namespace std;

const double INF = 1e9;
const double EPS = 1e-9;

struct pt {
    double x, y;

    pt() {}
    pt(double _x, double _y) : x(_x), y(_y) {}

    pt operator- (const pt &p) const {
        return pt(x - p.x, y - p.y);
    }

    pt operator+ (const pt &p) const {
        return pt(x + p.x, y + p.y);
    }

    pt operator* (double d) const {
        return pt(x * d, y * d);
    }

    pt operator/ (double d) const {
        return (*this) * (1 / d);
    }

    pt rotate90() const {
        return pt(-y, x);
    }

    pt norm() const {
        return (*this) / d();
    }

    double operator* (const pt &p) const {
        return x * p.y - y * p.x;
    }

    double operator% (const pt &p) const {
        return x * p.x + y * p.y;
    }

    double d2() const {
        return (*this) % (*this);
    }

    double d() const {
        return sqrt(d2());
    }
};

pt mirror(pt a, pt b, pt p) {
    pt v = (b - a).norm();
    pt n = v.rotate90();
    pt res = p + n * (-2 * ((p - a) % n));
    return res;
}

double dist(pt a, pt b, pt p) {
    return (p - (p + mirror(a, b, p))*0.5).d();
}

bool intersect(double x1, double x2, double x3, double x4) {
    double l1 = min(x1, x2), r1 = max(x1, x2);
    double l2 = min(x3, x4), r2 = max(x3, x4);
    return max(l1, l2) <= min(r1, r2) + EPS;
}

int sign(double x) {
    if (x > EPS) return 1;
    if (x < -EPS) return -1;
    return 0;
}

bool intersect(pt A, pt B, pt C, pt D) {
    bool res = 1;
    res &= intersect(A.x, B.x, C.x, D.x);
    res &= intersect(A.y, B.y, C.y, D.y);
    res &= sign((C - A) * (B - A)) * sign((D - A) * (B - A)) <= 0;
    res &= sign((A - C) * (D - C)) * sign((B - C) * (D - C)) <= 0;
    return res;
}


double solve(vector<vector<pt>> a) {
    int n = a.size() - 2;

    double ans = INF;
    for (int mask = 0; mask < (1 << n); mask++) {
        auto b = a;
        for (int i = 1; i <= n; i++) {
            if (mask & (1 << (i - 1))) {
                for (int j = i + 1; j <= n + 1; j++) {
                    for (int t = 0; t < 2; t++) {
                        b[j][t] = mirror(b[i][0], b[i][1], b[j][t]);
                    }
                }
            }
        }

        vector<vector<double>> dp(n + 2, vector<double>(2, INF));
        dp[0][0] = dp[0][1] = 0;
        for (int i = 0; i <= n; i++) {
            for (int ti = 0; ti < 2; ti++) {
                for (int j = i + 1; j <= n + 1; j++) {
                    for (int tj = 0; tj < 2; tj++) {
                        bool ok = 1;
                        double last_dist = 0;
                        for (int k = i + 1; k < j; k++) {
                            ok &= intersect(b[i][ti], b[j][tj], b[k][0], b[k][1]);
                            double cur_dist = dist(b[k][0], b[k][1], b[i][ti]);
                            ok &= cur_dist >= last_dist - EPS;
                            last_dist = cur_dist;
                        }
                        if (ok) {
                            dp[j][tj] = min(dp[j][tj], dp[i][ti] + (b[i][ti] - b[j][tj]).d());
                        }
                    }
                }
            }
        }
        double cans = min(dp[n + 1][0], dp[n + 1][1]);
        ans = min(ans, cans);
    }
    return ans;
}

int main() {
    cout.precision(10);
    cout << fixed;

    int n;
    cin >> n;
    vector<vector<pt>> a(n + 2, vector<pt>(2));
    cin >> a[0][0].x >> a[0][0].y;
    a[0][1] = a[0][0];
    for (int i = 1; i <= n; i++) for (int j = 0; j < 2; j++) cin >> a[i][j].x >> a[i][j].y;
    cin >> a[n+1][0].x >> a[n+1][0].y;
    a[n+1][1] = a[n+1][0];

    cout << solve(a) << endl;
}
