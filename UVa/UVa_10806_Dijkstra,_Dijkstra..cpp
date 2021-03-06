#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

const long long INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 110;
const int MAXM = 10010;
struct Edge {
	int u, v, next;
	long long c, w;
	Edge(int u0 = 0, int v0 = 0, long long c0 = 0, long long w0 = 0, int next0 = 0) {
		u = u0; v = v0; c = c0; w = w0; next = next0;
	}
} edge[MAXM * 4];
int head[MAXN], cnt;

bool visited[MAXN];
int path[MAXN], from, to, n, m;
long long dist[MAXN], ans;

void init() {
	memset(head, -1, sizeof(head));
	cnt = 0;
}

void addEdge(int u, int v, long long c, long long w) {
	edge[cnt] = Edge(u, v, c, w, head[u]);
	head[u] = cnt++;
	edge[cnt] = Edge(v, u, 0, -w, head[v]);
	head[v] = cnt++;
}

void input() {
    cin >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        addEdge(u, v, 1, w);
        addEdge(v, u, 1, w);
    }
    addEdge(0, 1, 2, 0);
    addEdge(1, 0, 2, 0);
    addEdge(n, n+1, 2, 0);
    addEdge(n+1, n, 2, 0);

    from = 0;  to = n+1;
}

bool findPath() {
	queue <int> q;
	memset(visited, false, sizeof(visited));
	memset(path, -1, sizeof(path));
	memset(dist, 0x3f, sizeof(dist));

	dist[from] = 0;
	visited[from] = true;
	q.push(from);

	while (!q.empty()) {
		int u = q.front();
		q.pop();

		for (int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].v;
            if (edge[i].c > 0 && dist[u] + edge[i].w < dist[v]) {
                dist[v] = dist[u] + edge[i].w;
                path[v] = i;
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
		}

		visited[u] = false;
	}

	return dist[to] != INF;
}

long long MinCostMaxFlow() {
    long long offflow, maxflow = 0, ret = 0;

	while (findPath()) {
		offflow = INF;
		for (int i = path[to]; i != -1; i = path[edge[i].u]) {
			offflow = min(offflow, edge[i].c);
		}
		for (int i = path[to]; i != -1; i = path[edge[i].u]) {
			edge[i].c -= offflow;
			edge[i ^ 1].c += offflow;
		}
		maxflow += offflow;
		ret += dist[to] * offflow;
	}

	return maxflow == 2 ? ret : -1;
}

void work() {
    ans = MinCostMaxFlow();
}

void output() {
    if (ans == -1) {
        cout << "Back to jail" << endl;
    } else {
        cout << ans << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
	while (cin >> n && n) {
		init();
		input();
		work();
		output();
	}
	return 0;
}

