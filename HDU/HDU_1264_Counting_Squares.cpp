#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 110;
bool covered[MAXN][MAXN];
int ans, x1, y1, x2, y2;

void init() {
    memset(covered, false, sizeof(covered));
    ans = 0;
}

void input() {
    do {
        int a = min(x1, x2), b = max(x1, x2);
        int c = min(y1, y2), d = max(y1, y2);
        for (int i = a; i < b; i++) {
            for (int j = c; j < d; j++) {
                covered[i][j] = true;
            }
        }
    } while (cin >> x1 >> y1 >> x2 >> y2 && x1 >= 0 && y1 >= 0 && x2 >= 0 && y2 >= 0);
}

void work() {
    for (int i = 0; i <= 100; i++) {
        for (int j = 0; j <= 100; j++) {
            if (covered[i][j]) {
                ans++;
            }
        }
    }
}

void output() {
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> x1 >> y1 >> x2 >> y2) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
