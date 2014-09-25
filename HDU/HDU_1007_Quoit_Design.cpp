#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
using namespace std;

const int MAXN = 100010;
const double eps = 1e-8;

int n, s[MAXN];
double ans;

int cmp(double x) {
	if (fabs(x) < eps) return 0;
	if (x > 0) return 1;
	return -1;
}

inline double sqr(double x) {
	return x * x;
}

struct point {
	double x, y;
	point() {}
	point(double a, double b) :x(a), y(b) {}
	friend point operator - (const point &a, const point &b) {
		return point(a.x - b.x, a.y - b.y);
	}
	double norm() {
		return sqrt(sqr(x) + sqr(y));
	}
} a[MAXN];

bool cmpx(int i, int j) {
    return cmp(a[i].x - a[j].x) < 0;
}

bool cmpy(int i, int j) {
    return cmp(a[i].y - a[j].y) < 0;
}

double min_dist(point a[], int s[], int l, int r) {
    //double ans = 1e100;
    if (r - l < 20) {
        for (int q = l; q < r; q++) {
            for (int w = q+1; w < r; w++) {
                ans = min(ans, (a[s[q]]-a[s[w]]).norm());
            }
        }
        return ans;
    }
    int tl, tr, m = (l+r) / 2;
    ans = min(min_dist(a, s, l, m), min_dist(a, s, m, r));
    for (tl = l; a[s[tl]].x < a[s[m]].x - ans; tl++);
    for (tr = r-1; a[s[tr]].x > a[s[m]].x + ans; tr--);
    sort(s+tl, s+tr, cmpy);
    for (int q = tl; q < tr; q++) {
        for (int w = q+l; w < min(tr, q+6); w++) {
            ans = min(ans, (a[s[q]]-a[s[w]]).norm());
        }
    }
    sort(s+tl, s+tr, cmpx);
    return ans;
}
double Min_Dist(point a[], int s[], int n) {
    for (int i = 0; i < n; i++) {
        s[i] = i;
    }
    sort(s, s+n, cmpx);
    return min_dist(a, s, 0, n);
}

void init() {
    memset(a, 0, sizeof(a));
    memset(s, 0, sizeof(s));
    ans = 1e100;
}

void input() {
    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y;
    }
}

void work() {
    ans = Min_Dist(a, s, n) / 2.0;
}

void output() {
    cout << fixed << setprecision(2) << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n && n) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
