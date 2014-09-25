#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 100010;
const int MAXM = 200010;
struct Edge {
    int u, v, c, next;
    Edge(int u0 = 0, int v0 = 0, int c0 = 0, int next0 = 0) {
        u = u0;
        v = v0;
        c = c0;
        next = next0;
    }
} edge[MAXM];
int head[MAXN], cnt;
bool visited[MAXN];
int path[MAXN], from, to, maxflow, offflow, N, M, nCase;;

void init() {
    memset(head, -1, sizeof(head));
    cnt = 0;
    maxflow = 0;
}

void addEdge(int u, int v, int c) {
    edge[cnt] = Edge(u, v, c, head[u]);
    head[u] = cnt++;
    edge[cnt] = Edge(v, u, c, head[v]);
    head[v] = cnt++;
}

void input() {
    int westernmost = INF, easternmost = -INF, s, t;

    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        if (x < westernmost) {
            westernmost = x;
            s = i;
        }
        if (x > easternmost) {
            easternmost = x;
            t = i;
        }
    }

    from = 0;
    to = N + 1;
    addEdge(from, s, INF);
    addEdge(t, to, INF);

    for (int i = 0; i < M; i++) {
        int l1, l2, c;
        scanf("%d%d%d", &l1, &l2, &c);
        addEdge(l1, l2, c);
        //addEdge(l2, l1, c);
    }
}

bool bfs() {
    int s = from, d;
    queue <int> q;
    q.push(s);
    memset(visited, false, sizeof(visited));
    while (!q.empty()) {
        s = q.front();
        q.pop();
        visited[s] = true;
        for (int i = head[s]; i != -1; i = edge[i].next) {
            d = edge[i].v;
            if (!visited[d] && edge[i].c > 0) {
                path[d] = i;
                q.push(d);
                if (d == to) return true;
            }
        }
    }
    return false;
}

void work() {
    while (bfs()) {
        offflow = INF;
        for (int i = to; i != from; i = edge[path[i]].u) {
            if (edge[path[i]].c < offflow)
                offflow = edge[path[i]].c;
        }
        for (int i = to; i != from; i = edge[path[i]].u) {
            edge[path[i]].c -= offflow;
            edge[path[i] ^ 1].c += offflow;
        }
        maxflow += offflow;
    }
}

void output() {
    printf("%d\n", maxflow);
}

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
