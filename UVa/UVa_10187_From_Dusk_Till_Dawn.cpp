#include <iostream>
#include <string>
#include <queue>
#include <map>
using namespace std;

const int MAXN = 110;

struct State {
    int city, time, litres;
    bool operator<(const State b) const {
        return litres > b.litres;
    }
};
priority_queue <State> q;

struct Route {
    int depart, arrive, to;
};
vector <Route> edges[MAXN];

int cnt, from, to, nCase, n, departure, during;
string start, destination;
map <string, int> cities;

void init() {
    cnt++;
    for (int i = 0; i < MAXN; i++) {
        edges[i].clear();
    }
    cities.clear();
    while (!q.empty()) q.pop();
}

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> start >> destination >> departure >> during;
        if (cities.find(start) == cities.end()) {
            from = cities.size();
            cities[start] = from;
        } else {
            from = cities[start];
        }
        if (cities.find(destination) == cities.end()) {
            to = cities.size();
            cities[destination] = to;
        } else {
            to = cities[destination];
        }

        if (departure <= 6) {
            departure += 24;
        }

        if (departure >= 18 && departure+during <= 24+6) {
            edges[from].push_back((Route){departure, departure+during, to});
        }
    }

    cin >> start >> destination;
}

int travel() {
    q.push((State){from, 18, 0});

    while (!q.empty()) {
        State cur = q.top();
        q.pop();

        if (cur.city == to) {
            return cur.litres;
        }

        for (int i = 0; i < edges[cur.city].size(); i++) {
            int usedBlood = cur.litres;
            if (cur.time > edges[cur.city][i].depart) {
                usedBlood++;
            }
            q.push((State){edges[cur.city][i].to, edges[cur.city][i].arrive, usedBlood});
        }
    }

    return -1;
}

void work() {
    cout << "Test Case " << cnt << "." << endl;
    if (start == destination) {
        cout << "Vladimir needs 0 litre(s) of blood." << endl;
        return;
    }

    if (cities.find(start) == cities.end()
    || cities.find(destination) == cities.end()) {
        cout << "There is no route Vladimir can take." << endl;
        return;
    }

    from = cities[start];
    to = cities[destination];

    int litres = travel();

    if (litres == -1) {
        cout << "There is no route Vladimir can take." << endl;
    } else {
        cout << "Vladimir needs " << litres << " litre(s) of blood." << endl;
    }
}

int main() {
    cin >> nCase;
    while (nCase--) {
        init();
        input();
        work();
    }
    return 0;
}
