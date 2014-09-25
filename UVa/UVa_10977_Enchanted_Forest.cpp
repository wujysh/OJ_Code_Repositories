#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 210;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
bool graph[MAXN][MAXN], visited[MAXN][MAXN];
int R, C, ans, m, n;
struct State {
    int x, y, t;
};

void init() {
    ans = INF;
    memset(graph, true, sizeof(graph));
    memset(visited, false, sizeof(visited));
}

void Jigglypuff(int x, int y, int L) {
    for (int i = x-L; i <= x+L; i++) {
        for (int j = y-L; j <= y+L; j++) {
            if (i >= 1 && i <= R && j >= 1 && j <= C) {
                if ((i-x)*(i-x) + (j-y)*(j-y) <= L*L) {
                    graph[i][j] = false;
                }
            }
        }
    }
}

void input() {
    cin >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        graph[x][y] = false;
    }
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y, L;
        cin >> x >> y >> L;
        Jigglypuff(x, y, L);
    }

//    for (int i = 1; i <= R; i++) {
//        for (int j = 1; j <= C; j++) {
//            cout << graph[i][j] << " ";
//        }
//        cout << endl;
//    }
}

void work() {
    queue <State> q;
    q.push((State){1, 1, 0});

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        if (cur.x == R && cur.y == C) {
            ans = min(ans, cur.t);
            return;
        }

        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if (nx >= 1 && nx <= R && ny >= 1 && ny <= C) {
                if (graph[nx][ny] && !visited[nx][ny]) {
                    q.push((State){nx, ny, cur.t+1});
                    visited[nx][ny] = true;
                }
            }
        }
    }
}

void output() {
    if (ans == INF) {
        cout << "Impossible." << endl;
    } else {
        cout << ans << endl;
    }
}

int main() {
    while (cin >> R >> C && (R || C)) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
