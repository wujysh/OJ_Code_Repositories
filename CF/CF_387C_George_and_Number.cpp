#include <iostream>
#include <string>
using namespace std;

string a;
int ans;

bool big(int s1, int s2) {
    if (s1 + 1 > s2 - s1) return true;
    else if (s1 + 1 < s2 - s1) return false;
    int i, j;
    for (i = 0, j = s1 + 1; i <= s1; i++, j++) {
        if (a[i] > a[j]) return true;
        else if (a[i] < a[j]) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    while (getline(cin, a)) {
        int len = a.length();
        for (int i = 0; i < len; i++) {
            if (i + 1 < len && a[i + 1] == '0') continue;
            ans = 1;
            int k = i;
            for (int j = k + 1; j < len; j++) {
                if (j + 1 < len && a[j + 1] == '0') continue;
                if (big(k, j)) {
                    ans++;
                    k = j;
                } else break;
            }
            if (k == len - 1) break;
        }
        cout << ans << endl;
    }
    return 0;
}
