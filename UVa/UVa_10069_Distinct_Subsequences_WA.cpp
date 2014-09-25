#include <iostream>
#include <cstring>
#include <string>
using namespace std;

const int MAXX = 10010, MAXZ = 110;
string X, Z;
long long dp[MAXZ][MAXX];// [pos of Z][pos of X]
int nCase;

void init() {
    memset(dp, -1, sizeof(dp));
}

void input() {
    getline(cin, X);
    getline(cin, Z);
}

int DP(int x, int y) {
    //cout << x << ", " << y << endl;
    if (dp[x][y] != -1) return dp[x][y];
    if (x == Z.length() && y <= X.length()) {
        return dp[x][y] = 1;
    }
    if (y >= X.length()) {
        return dp[x][y] = 0;
    }

    dp[x][y] = 0;
    for (int i = y; i < X.length(); i++) {
        //cout << x << ", " << i << endl;
        if (X[i] == Z[x]) {
            //cout << "- " << X[i] << Z[x] << endl;
            dp[x][y] += DP(x+1, i+1);
        }
    }
    return dp[x][y];
}

void work() {
    cout << DP(0, 0) << endl;
}

int main() {
    cin >> nCase;
    cin.ignore();
    while (nCase--) {
        init();
        input();
        work();
    }
    return 0;
}
