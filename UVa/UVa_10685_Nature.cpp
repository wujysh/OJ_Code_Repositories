#include <iostream>
#include <string>
#include <map>
using namespace std;

const int MAXN = 5010;
map <string, int> creatures;
int ans, C, R, father[MAXN], rank[MAXN];

int FindSet(int i){
    if (i != father[i])
        father[i] = FindSet(father[i]);
    return father[i];
}

void Union(int x, int y){
    if (rank[x] < rank[y])
        father[y] = x, rank[x] += rank[y];
    else
        father[x] = y, rank[y] += rank[x];
}

void init() {
    for (int i = 0; i < C; i++) {
        father[i] = i, rank[i] = 1;
    }
    ans = 0;
    creatures.clear();
}

void input() {
    for (int i = 0; i < C; i++) {
        string creature;
        cin >> creature;
        creatures[creature] = i;
//        if (creatures.find(creature) == creatures.end()) {
//            creatures[creature] = creatures.size();
//        }
    }
    for (int i = 0; i < R; i++) {
        string prey, predator;
        cin >> prey >> predator;

        int x = FindSet(creatures[predator]);
        int y = FindSet(creatures[prey]);
        if (x != y) {
            Union(x, y);
        }
    }
}

void work() {
    for (int i = 0; i < C; i++) {
        ans = max(ans, rank[i]);
    }
}

void output() {
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> C >> R && (C || R)) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
