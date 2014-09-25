#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 110;
const int INF = 32000;
const string op = "+-*/=";
int nCase, n, num[MAXN], target, path[MAXN];
bool dp[MAXN][INF*2+10];
bool vis[MAXN][INF*2+10];

void init() {
    memset(dp, false, sizeof(dp));
    memset(vis, false, sizeof(vis));
    memset(num, 0, sizeof(num));
    memset(path, -1, sizeof(path));
}

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> num[i];
    }
    cin >> target;
}

bool DP(int n, int sum) {

    if (vis[n][sum+INF]) return dp[n][sum+INF];
    vis[n][sum+INF] = true;

    if (n == 1) {
        if (sum == num[1]) {
            return dp[n][sum+INF] = true;
        } else {
            return dp[n][sum+INF] = false;
        }
    }

    int nextSum;

    nextSum = sum - num[n];
    if (nextSum >= -INF && nextSum <= INF) {
        if (DP(n-1, nextSum)) {
            path[n] = 0;
            return dp[n][sum+INF] = true;
        }
    }

    nextSum = sum + num[n];
    if (nextSum >= -INF && nextSum <= INF) {
        if (DP(n-1, nextSum)) {
            path[n] = 1;
            return dp[n][sum+INF] = true;
        }
    }

    if (sum % num[n] == 0) {
        nextSum = sum / num[n];
        if (nextSum >= -INF && nextSum <= INF) {
            if (DP(n-1, nextSum)) {
                path[n] = 2;
                return dp[n][sum+INF] = true;
            }
        }
    }

    nextSum = sum * num[n];
    if (nextSum >= -INF && nextSum <= INF) {
        if (DP(n-1, nextSum)) {
            path[n] = 3;
            return dp[n][sum+INF] = true;
        }
    }

    return dp[n][sum+INF] = false;
}

void work() {
    if (DP(n, target)) {
        path[n+1] = 4;
        for (int i = 1; i <= n; i++) {
            cout << num[i] << op[path[i+1]];
        }
        cout << target << endl;
    } else {
        cout << "NO EXPRESSION" << endl;
    }
}

int main() {
    cin >> nCase;
    while (nCase--) {
        init();
        input();
        work();
    }
    return 0;
}

