#include <iostream>
using namespace std;

const int MAXN = 110;
const int INF = 0x3f3f3f3f;
int A[MAXN], B[MAXN], m, n, nCase;

void input() {
    cin >> m >> n;
    for (int i = 0; i < m; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> B[i];
    }
}

int calcF(int i, int j) {  // B[i], A[j]
    int x = B[i] ^ A[j], cnt = 0;
    while (x) {
        if (x & 1) cnt++;
        x >>= 1;
    }
    return cnt;
}

void solve() {
    for (int i = 0; i < n; i++) {  // B[i]
        int minF = INF, minA = INF;

        for (int j = 0; j < m; j++) {  // A[j]
            int f = calcF(i, j);
            if (f < minF) {
                minF = f;
                minA = A[j];
            } else if (f == minF && A[j] < minA) {
                minA = A[j];
            }
        }

        cout << minA << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> nCase;
    while (nCase--) {
        input();
        solve();
    }
    return 0;
}
