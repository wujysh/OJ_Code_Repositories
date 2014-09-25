#include <algorithm>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

priority_queue <int> q;
int n, m, ans1, ans2;

int main() {
    ios::sync_with_stdio(false);

    int i, mid, tmp;
    while (!q.empty()) q.pop();
    cin >> n;
    while (n--) {
        cin >> m;
        mid = m >> 1;
        for(i = 1; i <= mid; i++) {
            cin >> tmp;
            ans1 += tmp;
        }
        if (m & 1) {
            i++;
            cin >> tmp;
            q.push(tmp);
        }
        for (; i <= m; i++) {
            cin >> tmp;
            ans2 += tmp;
        }
    }
    while (!q.empty()) {
        ans1 += q.top();
        q.pop();
        if (q.empty()) break;
        ans2 += q.top();
        q.pop();
    }
    cout << ans1 << " " << ans2 << endl;

    return 0;
}
