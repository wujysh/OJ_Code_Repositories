#include <iostream>
#include <vector>
using namespace std;

vector <int> num;
int sum, n;

void init() {
    num.clear();
    sum = 0;
}

void input() {
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        num.push_back(x);
    }
}

void work() {
    bool changed = true;
    while (changed) {
        changed = false;
        for (int i = 0; i < num.size(); i++) {
            for (int j = 0; j < num.size(); j++) {
                if (i != j && num[i] > num[j]) {
                    num[i] -= num[j];
                    changed = true;
                }
            }
        }
    }
    for (int i = 0; i < num.size(); i++) {
        sum += num[i];
    }
}

void output() {
    cout << sum << endl;
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
