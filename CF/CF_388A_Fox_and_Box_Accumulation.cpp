#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 110;
int cnt[MAXN], strength[MAXN], ans, n, rest;
bool visited[MAXN];

void init() {
    memset(cnt, 0, sizeof(cnt));
    memset(visited, false, sizeof(visited));
    ans = 0;
}

void input() {
    for (int i = 0; i < n; i++) {
        cin >> strength[i];
    }
    rest = n;
}

void work() {
    sort(strength, strength+n);
    while (rest > 0) {
        int a = 0;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && strength[i] >= a) {
                visited[i] = true;
                rest--;
                a++;
            }
        }
        ans++;
    }
}

void output() {
    cout << ans << endl;
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
