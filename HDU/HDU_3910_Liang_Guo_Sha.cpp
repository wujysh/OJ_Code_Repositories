#include <iostream>
#include <iomanip>
using namespace std;

const double EPS = 1e-10;
double A, B, C, ans;

int main() {
    ios::sync_with_stdio(false);
    while (cin >> A >> B >> C) {
        ans = (A*B - C*C) / (A + B + 2*C) + EPS;
        cout << fixed << setprecision(6) << ans << endl;
    }
    return 0;
}
