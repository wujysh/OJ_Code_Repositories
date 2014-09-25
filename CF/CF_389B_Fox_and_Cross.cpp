#include <iostream>
#include <string>
using namespace std;

const int MAXN = 110;
string graph[MAXN];
bool ans;
int n;

void init() {
    ans = true;
}

void input() {
    cin.ignore();
    for (int i = 0; i < n; i++) {
        getline(cin, graph[i]);
    }
}

void work() {
    for (int i = 1; i < n-1; i++) {
        for (int j = 1; j < n-1; j++) {
            if (graph[i][j] == '#' && graph[i - 1][j] == '#' && graph[i + 1][j] == '#' && graph[i][j - 1] == '#' && graph[i][j + 1] == '#') {
                graph[i][j] = '.';
                graph[i - 1][j] = '.';
                graph[i + 1][j] = '.';
                graph[i][j - 1] = '.';
                graph[i][j + 1] = '.';
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == '#') {
                ans = false;
                return;
            }
        }
    }
}

void output() {
    if (ans) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
