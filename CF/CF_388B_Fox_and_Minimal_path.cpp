#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 1010;
bool f[MAXN][MAXN];
int g[MAXN], c = 2;

void solve(int x, int m) {
    if(x) {
        f[1][c + 1] = 1;
        f[1][c + 2] = 1;
        for(int i = 1; i <= 2 * (x - 1); i++) {
            int u = i + c;
            if(i % 2 == 0) {
                f[u][u + 1] = f[u][u + 2] = 1;
            } else {
                f[u][u + 2] = f[u][u + 3] = 1;
            }
        }
        c += 2 * x;
    }
    if(x == m) {
        g[0] = c;
        if(x) {
            f[2][c] = f[2][c - 1] = 1;
        } else {
            if(m) f[c][2] = f[2][c] = 1;
            else f[1][2] = 1;
        }
    } else {
        c++;
        if(x) f[c][c - 1] = f[c][c - 2] = 1;
        else f[1][c] = 1;
        for(int i = 0; i < m - x - 1; i++) {
            int &v = g[m - x - 2 - i];
            if(v) {
                f[c][v] = 1;
                return;
            } else {
                g[m - x - 1 - i] = c;
                f[c][c + 1] = 1;
                c++;
            }
        }
        f[2][c] = 1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    int n, k, m = 0;
    cin >> k;
    while (k) {
        int p = 0;
        while ((1 << p) <= k / 2) p++;
        m = max(m, p);
        solve(p, m);
        k -= 1 << p;
    }
    for (int i = 1; i <= c; i++)
        for (int j = 1; j <= c; j++)
            if (f[i][j])
                f[j][i] = true;

    cout << c << endl;
    for (int i = 1; i <= c; i++) {
        for (int j = 1; j <= c; j++) {
            if (f[i][j]) {
                cout << "Y";
            } else {
                cout << "N";
            }
        }
        cout << endl;
    }
    return 0;
}
