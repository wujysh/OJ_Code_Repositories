#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 10010;
string line;
int graph[MAXN][MAXN], maxv, ans;

void init() {
    memset(graph, INF, sizeof(graph));
    maxv = ans = 0;
}

void input() {
    do {
        stringstream ss(line);
        int a, b, l;
        ss >> a >> b >> l;
        graph[a][b] = graph[b][a] = l;
        maxv = max(maxv, max(a, b));
    } while (getline(cin, line) && line != "");
}

void work() {
    for (int i = 1; i <= maxv; i++) {
        for (int j = 1; j <= maxv; j++) {
            for (int k = 1; k <= maxv; k++) {
                graph[i][j] = min(graph[i][j], graph[i][k]+graph[k][j]);
            }
        }
    }
}

void output() {
    for (int i = 1; i <= maxv; i++) {
        for (int j = 1; j <= maxv; j++) {
            if (graph[i][j] != INF) {
                ans = max(ans, graph[i][j]);
            }
        }
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (getline(cin, line)) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
