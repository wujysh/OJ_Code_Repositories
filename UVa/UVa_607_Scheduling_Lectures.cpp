#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 1010;
const int INF = 0x3f3f3f3f;
int nCase, n, L, C, ans;
int t[MAXN], sum[MAXN], dp[MAXN][MAXN];

void init() {
    memset(t, 0, sizeof(t));
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i < MAXN; i++) {
        dp[i][0] = 0;
    }
}

void input() {
    cin >> L >> C;
    sum[0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
        sum[i] = sum[i-1] + t[i];
    }
}

int calcDI(int x) {
    int t = L - x;
    if (t == 0) return 0;
    if (t >= 1 && t <= 10) return -C;
    if (t > 10) return (t-10) * (t-10);
}

void work() {
    for (int i = 1; dp[i-1][n] == INF; i++) {  // number of lectures
        for (int j = i; j <= n && sum[j] <= i*L; j++) {  // last topic in the lecture
            for (int k = j; k >= i-1 && sum[j]-sum[k] <= L; k--) {  // first topic in the lecture
                // arrange the k+1 th to j th topics in the i th lecture
                if (dp[i-1][k] != INF) {
                    dp[i][j] = min(dp[i][j], dp[i-1][k] + calcDI(sum[j]-sum[k]));
                }
            }
        }
    }

    // find the minimum number of lectures to contain all topics
    for (int i = 1; i <= n; i++) {
        if (dp[i][n] != INF) {
            ans = i;
            break;
        }
    }
}

void output() {
    if (nCase++) cout << endl;
    cout << "Case " << nCase << ":" << endl;
    cout << "Minimum number of lectures: " << ans << endl;
    cout << "Total dissatisfaction index: " << dp[ans][n] << endl;
}

int main() {
    while (cin >> n && n) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
