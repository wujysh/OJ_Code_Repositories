#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 24*3600 + 10;
int n, ans, cnt[MAXN];

void init() {
    ans = 0;
    memset(cnt, 0, sizeof(cnt));
}

void input() {
    for (int i = 0; i < n; i++) {
        int beg, end;
        cin >> beg >> end;
        for (int j = beg; j <= end; j++) {
            cnt[j]++;
            if (cnt[j] > ans) {
                ans = cnt[j];
            }
        }
    }
}

void output() {
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n && n) {
        init();
        input();
        output();
    }
}
