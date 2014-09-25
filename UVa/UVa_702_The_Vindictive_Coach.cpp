#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 30;
long long dp[MAXN][MAXN][2];
int N, m;

void init() {
    memset(dp, 0, sizeof(dp));
    for (int k = 0; k < MAXN; k++) {
        for (int p = 0; p < 2; p++) {
            dp[0][k][p] = 1;
        }
    }
}

void work() {
    for (int n = 1; n < MAXN; n++) {  // total number of colleagues
        for (int k = 0; k <= n; k++) {  // current person
            for (int p = 0; p < 2; p++) {  // low-high or high-low
                for (int i = 0; i < n; i++) {
                    if (p == 0 && i >= k) continue;
                    if (p == 1 && i < k) continue;
                    dp[n][k][p] += dp[n-1][i][!p];
                }
            }
        }
    }
}

void output() {
    if (N <= 2) {
        cout << 1 << endl;
    } else {
        if (m == 1) {
            cout << dp[N-2][1][0] << endl;
        } else {
            cout << dp[N-1][m-1][0] << endl;
        }
    }
}

int main() {
    init();
    work();
    while (cin >> N >> m) {
        output();
    }
    return 0;
}
