#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN = 10;
const int INF = 0x3f3f3f3f;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
int startx, starty, endx, endy;
bool graph[MAXN][MAXN][MAXN][MAXN], visited[MAXN][MAXN];

struct State {
    int x, y, t;
    string path;
} resultState;
queue <State> q;

void init() {
    memset(graph, true, sizeof(graph));
    memset(visited, false, sizeof(visited));
    while (!q.empty()) q.pop();
}

void input() {
    cin >> endx >> endy;
    for (int i = 0; i < 3; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        if (x1 == x2) {
            for (int j = min(y1, y2); j <= max(y1, y2)-1; j++) {
                graph[x1][j][x1][j+1] = false;
            }
        } else if (y1 == y2) {
            for (int i = min(x1, x2); i <= max(x1, x2)-1; i++) {
                graph[i][y1][i+1][y1] = false;
            }
        }
    }
}

void work() {
    q.push((State){startx, starty, 0, ""});

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        if (cur.x == endx && cur.y == endy) {
            resultState = cur;
            return;
        }

        //printf("%d %d %d\n", cur.x, cur.y, cur.t);

        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if (nx >= 1 && nx <= 6 && ny >= 1 && ny <= 6) {
                int x1, y1, x2, y2;
                switch (i) {
                case 0:
                    x1 = x2 = nx;
                    y1 = ny - 1;
                    y2 = ny;
                    break;
                case 1:
                    y1 = y2 = ny - 1;
                    x1 = nx - 1;
                    x2 = nx;
                    break;
                case 2:
                    x1 = x2 = nx - 1;
                    y1 = ny - 1;
                    y2 = ny;
                    break;
                case 3:
                    y1 = y2 = ny;
                    x1 = nx - 1;
                    x2 = nx;
                    break;
                }
                if (graph[x1][y1][x2][y2] && !visited[nx][ny]) {
                    char nextPath;
                    switch (i) {
                    case 0:
                        nextPath = 'W';
                        break;
                    case 1:
                        nextPath = 'S';
                        break;
                    case 2:
                        nextPath = 'E';
                        break;
                    case 3:
                        nextPath = 'N';
                        break;
                    }
                    q.push((State){nx, ny, cur.t+1, cur.path+nextPath});
                    visited[nx][ny] = true;
                }
            }
        }
    }
}

void output() {
    cout << resultState.path << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> startx >> starty && (startx || starty)) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
