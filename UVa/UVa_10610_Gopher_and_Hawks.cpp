#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 1010;
struct Hole {
    double x, y;
    Hole(double x0 = 0, double y0 = 0) {
        x = x0;  y = y0;
    }
} startHole, targetHole;
vector <Hole> hole;
struct State {
    Hole hole;
    int cnt;
    State(Hole h0 = Hole(0, 0), int c0 = 0) {
        hole = h0;  cnt = c0;
    }
};
queue <State> q;
int metersPerMinute, v, m, ans;
bool vis[MAXN];

void init() {
    hole.clear();
    metersPerMinute = v * m * 60;
    ans = INF;
    memset(vis, false, sizeof(vis));
}

void input() {
    cin >> startHole.x >> startHole.y;
    cin >> targetHole.x >> targetHole.y;
    cin.ignore();
    string line;
    while (getline(cin, line) && line != "") {
        stringstream ss(line);
        double x, y;
        ss >> x >> y;
        hole.push_back(Hole(x, y));
    }
}

double calcDistance(Hole h1, Hole h2) {
    return sqrt((h1.x-h2.x) * (h1.x-h2.x) + (h1.y-h2.y) * (h1.y-h2.y));
}

void work() {
    q.push(State(startHole, 0));
    while (!q.empty()) {
        State cur = q.front();
        q.pop();
        if (calcDistance(cur.hole, targetHole) <= metersPerMinute) {
            ans = min(ans, cur.cnt);
        };
        for (int i = 0; i < hole.size(); i++) {
            if (!vis[i]) {
                if (calcDistance(cur.hole, hole[i]) <= metersPerMinute) {
                    vis[i] = true;
                    q.push(State(hole[i], cur.cnt+1));
                }
            }
        }
    }
}

void output() {
    if (ans == INF) {
        cout << "No." << endl;
    } else {
        cout << "Yes, visiting " << ans << " other holes." << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> v >> m && (v || m)) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
