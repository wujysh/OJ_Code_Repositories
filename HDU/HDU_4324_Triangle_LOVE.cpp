#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 2010;
vector<vector<int> > graph;
vector<int> inDegree;
int n, m, cnt, nCase;  // L[MAXN];
bool ans;

bool toposort() {
    int total = 0;
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (!inDegree[i]) q.push(i);
    }
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        total++;  // L[total++] = x;
        for (int j = 0; j < graph[x].size(); j++) {
            int t = graph[x][j];
            inDegree[t]--;
            if (!inDegree[t]) {
                q.push(t);
            }
        }
    }
    if (total == n) return true;
    return false;
}

void init() {
    cnt++;
    graph.clear();
    inDegree.clear();
}

void input() {
    cin >> n;
    cin.ignore();
    graph.resize(n);
    inDegree.resize(n);

    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);
        for (int j = 0; j < n; j++) {
            if (line[j] == '1') {
                graph[i].push_back(j);
                inDegree[j]++;
            }
        }
    }
}

void work() {
    ans = toposort();
}

void output() {
    cout << "Case #" << cnt << ": ";
    if (!ans) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
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
