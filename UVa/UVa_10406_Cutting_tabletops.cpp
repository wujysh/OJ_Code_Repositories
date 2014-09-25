#include <iostream>
#include <iomanip>
#include <functional>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

const int MAXN = 1010;
const double eps = 1e-8;

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
};
double det(const point &a, const point &b) {
	return a.x * b.y - a.y * b.x;
}
double dot(const point &a, const point &b) {
	return a.x * b.x + a.y * b.y;
}
double dist(const point &a, const point &b) {
	return (a-b).norm();
}

struct polygon {
    int n;
    point a[MAXN];
    polygon() {}
    double area() {
        double sum = 0;
        a[n] = a[0];
        for (int i = 0; i < n; i++) {
            sum += det(a[i+1], a[i]);
        }
        return sum / 2.0;
    }
} tabletop;

int n;
double ans, d;

void init() {
    tabletop.n = n;
}

void input() {
    for (int i = 0; i < n; i++) {
        cin >> tabletop.a[i].x >> tabletop.a[i].y;
    }
    tabletop.a[n] = tabletop.a[0];
}

void work() {
    ans = tabletop.area();
    for (int i = 0; i < n; i++) {
        ans -= dist(tabletop.a[i], tabletop.a[i+1]) * d;
    }
    for (int i = 0; i < n; i++) {
        point cur = tabletop.a[i];
        point left = tabletop.a[((i-1)+n) % n];
        point right = tabletop.a[(i+1) % n];
        point p1 = point(left.x-cur.x, left.y-cur.y);
        point p2 = point(right.x-cur.x, right.y-cur.y);
        double delta = acos(dot(p1, p2) / p1.norm() / p2.norm()) / 2.0;
        double triangle_area = d / (tan(delta)) * d;
        ans += triangle_area;
    }
}

void output() {
    cout << fixed << setprecision(3) << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> d >> n && (d || n)) {
        init();
        input();
        work();
        output();
    }
	return 0;
}
