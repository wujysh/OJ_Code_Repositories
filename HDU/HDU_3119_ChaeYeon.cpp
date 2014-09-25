#include <iostream>
#include <iomanip>
#include <algorithm>
#include <complex>
#include <cmath>
#include <vector>
using namespace std;

const double EPS = 1e-8;
const double INF = 1 << 20;
const double PI = acos(-1);

int nCase, R, G, B;
double area_all, area_white, area_blue, area_green, area_red, area_blue_red, area_green_red, area_blue_green;
double area_all_red, area_all_blue, area_all_green, area_magenta, area_yellow, area_cyan;

int cmp(double x) {
	if (fabs(x) < EPS) return 0;
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
	friend point operator + (const point &a, const point &b) {
		return point(a.x + b.x, a.y + b.y);
	}
	friend point operator - (const point &a, const point &b) {
		return point(a.x - b.x, a.y - b.y);
	}
	friend bool operator == (const point &a, const point &b) {
		return cmp(a.x - b.x) == 0 && cmp(a.y - b.y) == 0;
	}
	friend point operator * (const point &a, const double &b) {
		return point(a.x * b, a.y * b);
	}
	friend point operator * (const double &a, const point &b) {
		return point(a * b.x, a * b.y);
	}
	friend point operator / (const point &a, const double &b) {
		return point(a.x / b, a.y / b);
	}
	double norm() {
		return sqrt(sqr(x) + sqr(y));
	}
};

double cross(const point &a, const point &b) {
    return a.x*b.y - a.y*b.x;
}

struct Circle {
    point p;
    double r;
    Circle() {}
    Circle(point p0, double r0) : p(p0), r(r0) {}
    bool operator<(const Circle &o) const {
        if (cmp(r - o.r) != 0) return cmp(r - o.r) == -1;
        if (cmp(p.x - o.p.x) != 0) {
            return cmp(p.x - o.p.x) == -1;
        }
        return cmp(p.y - o.p.y) == -1;
    }

    bool operator==(const Circle &o) const {
        return cmp(r - o.r) == 0 && cmp(p.x - o.p.x == 0) &&
            cmp(p.y - o.p.y) == 0;
    }
};

point rotate(const point &p, double cost, double sint) {
    double x = p.x, y = p.y;
    return point(x*cost - y*sint, x*sint + y*cost);
}

pair<point, point> crosspoint(point ap, double ar, point bp, double br) {
    double d = (ap - bp).norm();
    double cost = (ar*ar + d*d - br*br) / (2*ar*d);
    double sint = sqrt(1.0 - cost*cost);
    point v = (bp - ap) / (bp - ap).norm() * ar;
    return make_pair(ap+rotate(v, cost, -sint), ap+rotate(v, cost, sint));
}

inline pair<point, point> crosspoint(const Circle &a, const Circle &b) {
    return crosspoint(a.p, a.r, b.p, b.r);
}

Circle c[1000], tc[1000];
vector <Circle> RC, GC, BC;
int n, m;

struct Node {
    point p;
    double a;
    int d;

    Node(const point &p, double a, int d) : p(p), a(a), d(d) {}
    bool operator<(const Node &o) const {
        return a < o.a;
    }
};

double arg(point p) {
    return arg(complex<double>(p.x, p.y));
}

double solve() {
    n = 0;
    sort(tc, tc + m);
    m = unique(tc, tc + m) - tc;
    for (int i = m - 1; i >= 0; i--) {
        bool ok = true;
        for (int j = i + 1; j < m; j++) {
            double d = (tc[i].p - tc[j].p).norm();
            if (cmp(d - abs(tc[i].r - tc[j].r)) <= 0) {
                ok = false;
                break;
            }
        }
        if (ok) c[n++] = tc[i];
    }
    double ans = 0;
    for (int i = 0; i < n; i++) {
        vector<Node> event;
        point boundary = c[i].p + point(-c[i].r, 0);
        event.push_back(Node(boundary, -PI, 0));
        event.push_back(Node(boundary, PI, 0));
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            double d = (c[i].p - c[j].p).norm();
            if (cmp(d - (c[i].r + c[j].r)) < 0) {
                pair<point, point> ret = crosspoint(c[i], c[j]);
                double x = arg(ret.first - c[i].p);
                double y = arg(ret.second - c[i].p);
                if (cmp(x - y) > 0) {
                    event.push_back(Node(ret.first, x, 1));
                    event.push_back(Node(boundary, PI, -1));
                    event.push_back(Node(boundary, -PI, 1));
                    event.push_back(Node(ret.second, y, -1));
                } else {
                    event.push_back(Node(ret.first, x, 1));
                    event.push_back(Node(ret.second, y, -1));
                }
            }
        }
        sort(event.begin(), event.end());
        int sum = event[0].d;
        for (int j = 1; j < (int)event.size(); j++) {
            if (sum == 0) {
                ans += cross(event[j - 1].p, event[j].p) / 2;
                double x = event[j - 1].a;
                double y = event[j].a;
                double area = c[i].r * c[i].r * (y - x) / 2;
                point v1 = event[j - 1].p - c[i].p;
                point v2 = event[j].p - c[i].p;
                area -= cross(v1, v2) / 2;
                ans += area;
            }
            sum += event[j].d;
        }
    }
    return ans;
}

void init() {
    RC.clear();
    GC.clear();
    BC.clear();
    area_all = area_white = area_blue = area_green = area_red = 0;
    area_blue_green = area_blue_red = area_green_red = 0;
    area_all_red = area_all_blue = area_all_green = 0;
    area_yellow = area_magenta = area_cyan = 0;
}

void input() {
    cin >> R >> G >> B;
    m = 0;
    for (int i = 0; i < R; i++) {
        double x, y, r;
        cin >> x >> y >> r;
        RC.push_back(Circle(point(x, y), r));
        tc[m++] = Circle(point(x, y), r);
    }
    for (int i = 0; i < G; i++) {
        double x, y, r;
        cin >> x >> y >> r;
        GC.push_back(Circle(point(x, y), r));
        tc[m++] = Circle(point(x, y), r);
    }
    for (int i = 0; i < B; i++) {
        double x, y, r;
        cin >> x >> y >> r;
        BC.push_back(Circle(point(x, y), r));
        tc[m++] = Circle(point(x, y), r);
    }
}

void work() {
    /// All
    m = R + G + B;
    area_all = solve();

    /// Blue and Red
    m = 0;
    for (int i = 0; i < B; i++) {
        tc[m++] = BC[i];
    }
    for (int i = 0; i < R; i++) {
        tc[m++] = RC[i];
    }
    m = B + R;
    area_blue_red = solve();

    /// Green and Red
    m = 0;
    for (int i = 0; i < G; i++) {
        tc[m++] = GC[i];
    }
    for (int i = 0; i < R; i++) {
        tc[m++] = RC[i];
    }
    m = G + R;
    area_green_red = solve();

    /// Blue and Green
    m = 0;
    for (int i = 0; i < B; i++) {
        tc[m++] = BC[i];
    }
    for (int i = 0; i < G; i++) {
        tc[m++] = GC[i];
    }
    m = B + G;
    area_blue_green = solve();

    /// All Red
    m = 0;
    for (int i = 0; i < R; i++) {
        tc[m++] = RC[i];
    }
    m = R;
    area_all_red = solve();

    /// All Green
    m = 0;
    for (int i = 0; i < G; i++) {
        tc[m++] = GC[i];
    }
    m = G;
    area_all_green = solve();

    /// All Blue
    m = 0;
    for (int i = 0; i < B; i++) {
        tc[m++] = BC[i];
    }
    m = B;
    area_all_blue = solve();

    area_red = area_all - area_blue_green;
    area_green = area_all - area_blue_red;
    area_blue = area_all - area_green_red;

    area_yellow = area_blue_red - area_all_blue - area_red;
    area_magenta = area_green_red - area_all_green - area_red;
    area_cyan = area_blue_red - area_all_red - area_blue;

    area_white = area_all - area_red - area_green - area_blue - area_yellow - area_magenta - area_cyan;
}

void output() {
    if (cmp(area_red) == 0) area_red = 0.0;
    if (cmp(area_green) == 0) area_green = 0.0;
    if (cmp(area_blue) == 0) area_blue = 0.0;
    if (cmp(area_white) == 0) area_white = 0.0;
    if (cmp(area_yellow) == 0) area_yellow = 0.0;
    if (cmp(area_magenta) == 0) area_magenta = 0.0;
    if (cmp(area_cyan) == 0) area_cyan = 0.0;
    cout << fixed << setprecision(2) << area_red << " " << area_green << " " << area_blue << " " << area_white << " " << area_yellow << " " << area_magenta << " " << area_cyan << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> nCase;
    while (nCase--) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
