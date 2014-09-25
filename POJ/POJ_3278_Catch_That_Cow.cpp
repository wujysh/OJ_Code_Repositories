#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN = 100010;
int ans, n, k;
bool visited[MAXN];

struct State{
    int x, t;
    State() {}
    State(int x0, int t0) : x(x0), t(t0) {}
};
queue<State> q;

void init() {
    memset(visited, false, sizeof(visited));
    visited[n] = true;
    while (!q.empty()) q.pop();
    q.push(State(n, 0));
}

void work() {
    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        if (cur.x == k) {
            ans = cur.t;
            return;
        }

        if (cur.x - 1 >= 0 && !visited[cur.x - 1]) {
            q.push(State(cur.x - 1, cur.t + 1));
            visited[cur.x - 1] = true;
        }
        if (cur.x + 1 < MAXN && !visited[cur.x + 1]) {
            q.push(State(cur.x + 1, cur.t + 1));
            visited[cur.x + 1] = true;
        }
        if (2 * cur.x < MAXN && !visited[2 * cur.x]) {
            q.push(State(2 * cur.x, cur.t + 1));
            visited[2 * cur.x] = true;
        }
    }
}

void output() {
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n >> k) {
        init();
        work();
        output();
    }
    return 0;
}
