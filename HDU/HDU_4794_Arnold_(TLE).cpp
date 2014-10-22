#include <iostream>
#include <cstdio>
using namespace std;

long long n;

void solve() {
    long long cnt = 1;
    long long xx = 1, yy = 2 % n;
    while (!(xx == 0 && yy == 1)) {
        xx = (xx + yy) % n;
        yy = (xx + yy) % n;
        cnt++;
    }
    printf("%I64d\n", cnt);
}

int main() {
    while (scanf("%I64d", &n) != EOF) {
        solve();
    }
    return 0;
}
