#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN = 30;
const int INF = 0x3f3f3f3f;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
struct State {
    int x, y, d, c, t;
};
queue <State> q;

int M, N, cnt, ans, startx, starty, targetx, targety;
bool graph[MAXN][MAXN], visited[MAXN][MAXN][4][5];

void init() {
    cnt++;
    ans = INF;
    memset(graph, false, sizeof(graph));
    memset(visited, false, sizeof(visited));
    while (!q.empty()) q.pop();
}

void input() {
    char ch;
    cin.ignore();
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cin >> ch;
            if (ch == '#') {
                graph[i][j] = false;
            } else {
                graph[i][j] = true;
            }
            if (ch == 'S') {
                startx = i;
                starty = j;
            }
            if (ch == 'T') {
                targetx = i;
                targety = j;
            }
        }
        cin.ignore();
    }
}

void work() {
    q.push((State){startx, starty, 0, 0, 0});
    visited[startx][starty][0][0] = true;

    while (!q.empty()) {
        State cur = q.front();
        q.pop();
        //printf("%d %d %d %d %d\n", cur.x, cur.y, cur.d, cur.c, cur.t);
        if (cur.x == targetx && cur.y == targety && cur.c == 0) {
            ans = min(ans, cur.t);
            return;
        }

        // Go ahead
        int nx = cur.x + dx[cur.d], ny = cur.y + dy[cur.d];
        if (nx >= 0 && nx < M && ny >= 0 && ny < N) {
            if (graph[nx][ny] && !visited[nx][ny][cur.d][(cur.c+1)%5]) {
                q.push((State){nx, ny, cur.d, (cur.c+1)%5, cur.t+1});
                visited[nx][ny][cur.d][(cur.c+1)%5] = true;
            }
        }

        // Turn left
        int nd = cur.d ? (cur.d-1)%4 : 3;  // Important!
        if (!visited[cur.x][cur.y][nd][cur.c]) {
            q.push((State){cur.x, cur.y, nd, cur.c, cur.t+1});
            visited[cur.x][cur.y][nd][cur.c] = true;
        }

        // Turn right
        if (!visited[cur.x][cur.y][(cur.d+1)%4][cur.c]) {
            q.push((State){cur.x, cur.y, (cur.d+1)%4, cur.c, cur.t+1});
            visited[cur.x][cur.y][(cur.d+1)%4][cur.c] = true;
        }
    }
}

void output() {
    if (cnt > 1) cout << endl;
    cout << "Case #" << cnt << endl;
    if (ans == INF) {
        cout << "destination not reachable" << endl;
    } else {
        cout << "minimum time = " << ans << " sec" << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> M >> N && (M || N)) {
        init();
        input();
        work();
        output();
    }
}
