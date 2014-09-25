#include <iostream>
#include <cstdio>
#include <iomanip>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN = 10100;
const int INF = 0x3f3f3f3f;
int nCase, n, dp[110][MAXN];
double ans;

struct Device {
    int b, p;
    Device() {}
    Device(int _b, int _p) : b(_b), p(_p) {}
};
vector<vector<Device> > devices;

//struct State {
//    int x, p, b;
//    State() {}
//    State(int _x, int _p, int _b) : x(_x), p(_p), b(_b) {}
//};
//queue<State> q;

void init() {
    devices.clear();
    memset(dp, -1, sizeof(dp));
    ans = 0;
//    while (!q.empty()) q.pop();
}

void input() {
    cin >> n;
    devices.resize(n);
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        for (int j = 0; j < m; j++) {
            int b, p;
            cin >> b >> p;
            devices[i].push_back(Device(b, p));
        }
    }
}

void work() {
///  Memory Limit Exceeded
//    q.push(State(0, 0, INF));
//    while (!q.empty()) {
//        State cur = q.front();
//        q.pop();
//
//        if (cur.x == n) {
//            ans = max(ans, (double)cur.b/cur.p);
//            continue;
//        }
//
//        for (int i = 0; i < devices[cur.x].size(); i++) {
//            q.push(State(cur.x+1, cur.p+devices[cur.x][i].p, min(cur.b, devices[cur.x][i].b)));
//        }
//    }

///  Accepted
    dp[0][0] = INF;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < devices[i].size(); j++) {
            for (int p = devices[i][j].p; p < MAXN; p++) {
                if (dp[i][p-devices[i][j].p] != -1) {
                    dp[i+1][p] = max(dp[i+1][p], min(dp[i][p-devices[i][j].p], devices[i][j].b));
                }
            }
        }
    }

    for (int i = 0; i < MAXN; i++) {
        if (dp[n][i] != -1) {
            //cout << i << " " << dp[n][i] << endl;
            ans = max(ans, (double)dp[n][i]/i);
        }
    }
}

void output() {
    cout << fixed << setprecision(3) << ans << endl;
}

int main() {
    //freopen("out.txt", "w", stdout);
    cin >> nCase;
    while (nCase--) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
