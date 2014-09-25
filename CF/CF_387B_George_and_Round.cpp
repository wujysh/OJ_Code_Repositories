#include<iostream>
using namespace std;

const int MAXN = 3010;
int a[MAXN], b[MAXN], n, m;

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n >> m) {
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int j = 0; j < m; j++) {
            cin >> b[j];
        }
        int i, j;
        for (i = 0, j = 0; i < n && j < m; j++) {
            if (b[j] >= a[i]) {
                i++;
            }
        }
        cout << n - i << endl;
    }
    return 0;
}
