#include <iostream>
using namespace std;

int K, N, M;
struct Query {
    int F1, F2, I;
    Query(int _F1, int _F2, int _I) : F1(_F1), F2(_F2), I(_I) {}
    bool operator<(const Query &b) const {
        return I < b.I;
    }
};
vector<Query> query;

struct Road {
    int F1, F2, L;
    char D;
    Road(int _F1, int _F2, int _L, int _D) : F1(_F1), F2(_F2), L(_L), D(_D) {}
};
vector<Road> road;




void init() {
    query.clear();
    road.clear();
    for (int i = 1; i <= N; i++) {
        father[i] = i;
    }
    cur = 0;
}

void input() {
    for (int i = 0; i < M; i++) {
        int F1, F2, L;
        char D;
        cin >> F1 >> F2 >> L >> D;
        road.push_back(Road(F1, F2, L, D));
    }
    cin >> K;
    for (int i = 0; i < K; i++) {
        int F1, F2, I;
        cin >> F1 >> F2 >> I;
        query.push_back(Query(F1, F2, I));
    }
}

void work() {
    sort(query.begin(), query.end());
    for (int i = 0; i < query.size(); i++) {
        for (int j = cur; j < query[i].I; j++) {
            addEdge();
        }

    }
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> N >> M) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
