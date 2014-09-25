#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
using namespace std;

int n, x, y;
string str1, str2;
vector<list<int> > v;

void init() {
    v.clear();
    for (int i = 0; i < n; i++) {
        list<int>l;
        l.push_back(i);
        v.push_back(l);
    }
}

void work() {
    list<int>::iterator it;
    int cnt, flag, i;

    for (i = 0; i < n; i++) {
        it = find(v[i].begin(), v[i].end(), x);
        if (it != v[i].end()) {
            cnt = i;
            break;
        }
    }
    for (i = 0; i < n; i++) {
        it = find(v[i].begin(), v[i].end(), y);
        if (it != v[i].end()) {
            flag = i;
            break;
        }
    }

    if (cnt == flag) {
        return;
    } else if (str1 == "move") {
        it = v[cnt].end();
        it--;
        for (; *it != x; it--) {
            v[*it].push_back(*it);
            v[cnt].erase(it);
        }
        v[cnt].erase(it);
        if (str2 == "onto") {
            it = v[flag].end();
            it--;
            for (; *it != y; it--) {
                v[*it].push_back(*it);
                v[flag].erase(it);
            }
            v[flag].push_back(x);
        } else
            v[flag].push_back(x);
    } else {
        if (str2 == "onto") {
            it = v[flag].end();
            it--;
            for (; *it != y; it--) {
                v[*it].push_back(*it);
                v[flag].erase(it);
            }
        }
        it = v[cnt].begin();
        for (; it != v[cnt].end(); it++) {
            if (*it == x) {
                for (; it != v[cnt].end(); it++)
                    v[flag].push_back(*it);
                break;
            }
        }
        it = v[cnt].end();
        it--;
        for (; *it != x; it--)
            v[cnt].erase(it);
        v[cnt].erase(it);
    }
}

void output() {
    list<int>::iterator it;
    for (int i = 0; i < n; i++) {
        cout << i << ":";
        for (it = v[i].begin(); it != v[i].end(); it++) {
            cout << " " << *it;
        }
        cout << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    init();
    while (cin >> str1 && str1 != "quit") {
        cin >> x >> str2 >> y;
        if (x != y) {
            work();
        }
    }
    output();

    return 0;
}
