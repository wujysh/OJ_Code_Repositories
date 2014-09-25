#include <iostream>
using namespace std;

int A, B, X, Y, D;

int extend_gcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;  y = 0;
        return a;
    } else {
        int r = extend_gcd(b, a%b, y, x);
        y -= x * (a/b);
        return r;
    }
}

void work() {
    D = extend_gcd(A, B, X, Y);
}

void output() {
    cout << X << " " << Y << " " << D << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> A >> B) {
        work();
        output();
    }
    return 0;
}
