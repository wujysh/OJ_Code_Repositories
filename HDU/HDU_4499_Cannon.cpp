#include <iostream>
#include <cstring>
using namespace std;

int N, M, Q, ans, graph[10][10], dp[10][10];
bool visited[10][10];

int dfs(int x, int y) {
    cout << x << " " << y << endl;
    int num = 0;

    if (graph[x][y]) return num;

    bool flag = false;
    for (int j = y-1; j >= 0; j--) {
        if (graph[x][j] && !flag) {
            flag = true;
            continue;
        }
        if (graph[x][j] == 2 && flag) {
            return num;
        }
    }

    flag = false;
    for (int j = y+1; j <= M-1; j++) {
        if (graph[x][j] && !flag) {
            flag = true;
            continue;
        }
        if (graph[x][j] == 2 && flag) {
            return num;
        }
    }

    flag = false;
    for (int i = x-1; i >= 0; i--) {
        if (graph[i][y] && !flag) {
            flag = true;
            continue;
        }
        if (graph[i][y] == 2 && flag) {
            return num;
        }
    }

    flag = false;
    for (int i = x+1; i <= N-1; i++) {
        if (graph[i][y] && !flag) {
            flag = true;
            continue;
        }
        if (graph[i][y] == 2 && flag) {
            return num;
        }
    }

    int ret = 0;
    for (int i = 0; i < N; i++) {
        if (i != x) {
            graph[x][y] = 2;
            //num++;
            //num += dfs(i, y);
            ret = max(ret, dfs() + 1);
            //num--;
            graph[x][y] = 0;
        }
    }

            //num++;
    for (int j = 0; j < M; j++) {
        if (j != y) {
            graph[x][y] = 2;
            //num += dfs(x, j);
            ret = max(ret, dfs() + 1);
            //num--;
            graph[x][y] = 0;
        }
    }

    return dp[x][y] = ret;
}

int main() {
    while (cin >> N >> M >> Q) {
        memset(graph, 0, sizeof(graph));
        memset(visited, false, sizeof(visited));
        ans = 0;

        for (int i = 0; i < Q; i++) {
            int x, y;
            cin >> x >> y;
            graph[x][y] = 1;
        }
/*
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                ans = max(ans, dfs(i, j));
            }
        }
        */

        cout << dfs(0, 0) << endl;
    }
    return 0;
}
