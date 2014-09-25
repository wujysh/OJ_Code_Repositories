#include <iostream>
#include <cstring>
#include <queue>
#include <set>
using namespace std;

const int MAXN = 5;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, -1, 0, 1};
struct State {
    int x, y;
    int puzzle[MAXN][MAXN];
    int distance;
    string path;
    State() {
        x = y = distance = 0;
        path = "";
        memset(puzzle, 0, sizeof(puzzle));
    }
    State(int x0, int y0, int p0[MAXN][MAXN], int d0, string path0) {
        x = x0;  y = y0;
        memcpy(puzzle, p0, sizeof(puzzle));
        distance = d0;
        path = path0;
    }
} initialState, resultState;
queue <State> q;
set <long long> vis;
int nCase, cnt, initialPuzzle[MAXN][MAXN], initialX, initialY;

void init() {
    cnt++;
    memset(initialPuzzle, 0, sizeof(initialPuzzle));
    resultState = State();
    vis.clear();
}

void input() {
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            cin >> initialPuzzle[i][j];
            if (initialPuzzle[i][j] == 0) {
                initialX = i;
                initialY = j;
            }
        }
    }
    //cout << initialX << " " << initialY << endl;
}

bool isVisited(int puzzle[MAXN][MAXN]) {
    long long token = 0;
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            token = token * 10 + puzzle[i][j];
        }
    }
    //cout << "isVisited: " << token << endl;  // Debug
    if (vis.find(token) != vis.end()) {
        return true;
    }
    return false;
}

void setVisited(int puzzle[MAXN][MAXN]) {
    long long token = 0;
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            token = token * 10 + puzzle[i][j];
        }
    }
    //cout << "setVisited: " << token << endl;  // Debug
    vis.insert(token);
}

void work() {
    q.push(State(initialX, initialY, initialPuzzle, 0, ""));
    while (!q.empty()) {
        State cur = q.front();
        q.pop();
        //cout << cur.x << " " << cur.y << endl;
        setVisited(cur.puzzle);
        if (cur.distance > resultState.distance) {
            resultState = cur;
        }

        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if (nx > 0 && nx < 4 && ny > 0 && ny < 4) {
                int nextPuzzle[MAXN][MAXN];
                memcpy(nextPuzzle, cur.puzzle, sizeof(nextPuzzle));
                swap(nextPuzzle[cur.x][cur.y], nextPuzzle[nx][ny]);
                if (!isVisited(nextPuzzle)) {
                    char nextPath;
                    switch (i) {
                    case 0:
                        nextPath = 'U';
                        break;
                    case 1:
                        nextPath = 'L';
                        break;
                    case 2:
                        nextPath = 'D';
                        break;
                    case 3:
                        nextPath = 'R';
                        break;
                    }
                    q.push(State(nx, ny, nextPuzzle, cur.distance+1, cur.path+nextPath));
                }
            }
        }
    }
}

void output() {
    cout << "Puzzle #" << cnt << endl;
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            if (j > 1) cout << " ";
            cout << resultState.puzzle[i][j];
        }
        cout << endl;
    }
    cout << resultState.path << endl;
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> nCase;
    while (nCase--) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
