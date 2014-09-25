#include <cstdio>
using namespace std;

int h1, m1, h2, m2, d;

int main() {
    while (~scanf("%d:%d %d:%d", &h1, &m1, &h2, &m2)) {
        d = (h1 * 60 + m1) - (h2 * 60 + m2);
        if (d < 0) {
            d += 24 * 60;
        }

        printf("%02d:%02d\n", d / 60, d % 60);
    }
    return 0;
}
