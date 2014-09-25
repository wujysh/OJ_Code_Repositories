#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
using namespace std;

const int MAXN = 110;
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};
int graph[MAXN][MAXN], a, b, n, cnt;
bool vis[MAXN][MAXN], ans;

void init() {
    memset(graph, 0, sizeof(graph));
    memset(vis, false, sizeof(vis));
    ans = true;
}

void input(int i) {
    string line;
    getline(cin, line);
    if (ans) {
        stringstream ss(line);
        while (ss >> a >> b) {
            graph[a][b] = i;
        }
    }
}

void dfs(int x, int y) {
    vis[x][y] = true;
    cnt++;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx >= 1 && nx <= n && ny >= 1 && ny <= n) {
            if (graph[nx][ny] == graph[x][y] && !vis[nx][ny]) {
                dfs(nx, ny);
            }
        }
    }
}

void work() {
    cin.ignore();
    for (int i = 1; i <= n-1; i++) {
        cnt = 0;
        input(i);
        if (ans) {
            dfs(a, b);
            if (cnt < n) {
                ans = false;
            }
        }
    }
    if (ans) {
        cnt = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (graph[i][j] == 0) {
                    dfs(i, j);
                    if (cnt < n) {
                        ans = false;
                    }
                    return;
                }
            }
        }
    }
}

void output() {
    if (ans) {
        cout << "good" << endl;
    } else {
        cout << "wrong" << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n && n) {
        init();
        work();
        output();
    }
    return 0;
}
