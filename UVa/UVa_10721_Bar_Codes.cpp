#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 55;
long long dp[MAXN][MAXN];
int n, k, m;

void init() {
    memset(dp, -1, sizeof(dp));
}

long long DP(int n, int k) {
    if (n < 0 || k < 0) return 0;
    if (dp[n][k] != -1) return dp[n][k];
    if (n > k*m || n < k) return dp[n][k] = 0;
    if (n == k*m || n == k) return dp[n][k] = 1;

    dp[n][k] = 0;
    for (int i = 1; i <= m; i++) {
        dp[n][k] += DP(n-i, k-1);
    }
    return dp[n][k];
}

void work() {
    cout << DP(n, k) << endl;
}

int main() {
    while (cin >> n >> k >> m) {
        init();
        work();
    }
    return 0;
}
