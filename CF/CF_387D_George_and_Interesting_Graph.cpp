#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 510;
const int INF = 0x3f3f3f3f;
bool graph[MAXN][MAXN], visited[MAXN];
int inDegree[MAXN], outDegree[MAXN], path[MAXN];
int ans, n, m;

void init() {
    ans = INF;
    memset(graph, false, sizeof(graph));
    memset(inDegree, 0, sizeof(inDegree));
    memset(outDegree, 0, sizeof(outDegree));
}

void input() {
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a][b] = true;
        outDegree[a]++;
        inDegree[b]++;
    }
}

bool findPath(int center, int u) {
    for (int i = 1; i <= n; i++) {
        if (i != center && graph[u][i]) {
            if (!visited[i]) {
                visited[i] = true;
                if (path[i] == -1 || findPath(center, path[i])) {
                    path[i] = u;
                    return true;
                }
            }
        }
    }
    return false;
}

int hungarian(int center) {
    int match = 0;
    memset(path, -1, sizeof(path));
    for (int i = 1; i <= n; i++) {
        if (i != center) {
            memset(visited, false, sizeof(visited));
            if (findPath(center, i)) match++;
        }
    }
    return match;
}

void work() {
    for (int i = 1; i <= n; i++) {
        // the center i should bi connect other vertexes and self loop
        int arcs_center = inDegree[i] + outDegree[i] - graph[i][i];
        int res = 2 * (n-1) + 1 - arcs_center;  // add arcs to meet the criteria 2

        // bipartite match among other vertexes
        int arcs_remain = hungarian(i);

        // add or remove arcs to meet the criteria 3
        res += m - arcs_center - arcs_remain;  // remove arcs
        res += n - 1 - arcs_remain; // add arcs

        ans = min(ans, res);
    }
}

void output() {
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n >> m) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
