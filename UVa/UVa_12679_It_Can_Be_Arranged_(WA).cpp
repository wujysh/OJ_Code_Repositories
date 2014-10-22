#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cstdio>
using namespace std;

bool flag;
int cnt1;

struct Classroom {
    int endTime;
    int courseNo;
};

struct Course {
    int startTime, endTime, num, id;
    bool operator < (const Course &b) const {
        return startTime < b.startTime;
    }
} course[110];

int clean[110][110], cnt, N, M, nCase;

void input() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d%d%d", &course[i].startTime, &course[i].endTime, &course[i].num);
        course[i].id = i;
    }

    sort(course, course+N);
    int index[110];
    for (int i = 0; i < N; i++) {
        index[course[i].id] = i;
    }
    /*
    for (int i = 0; i < N; i++) {
        cout << i << " " << index[i] << endl;
    }
    */
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &clean[index[i]][index[j]]);
        }
    }
    /*
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", clean[i][j]);
        }
        cout << endl;
    }*/
}

void solve() {
    //sort(course, course+N);

    vector<Classroom> classroom;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < classroom.size(); j++) {
            if (classroom[j].endTime <= course[i].startTime && course[i].num > 0) {
                if (classroom[j].endTime + clean[classroom[j].courseNo][i] < course[i].startTime) {
                    classroom[j].courseNo = i;
                    classroom[j].endTime = course[i].endTime;
                    course[i].num -= M;
                    //cout << i << " " << j << endl;
                    cout << "Classroom " << j << " for course " << i << endl;
                }
            }
        }
        while (course[i].num > 0) {
            Classroom cls;
            cls.courseNo = i;
            cls.endTime = course[i].endTime;
            course[i].num -= M;
            classroom.push_back(cls);
            //cout << "!" << i  << " " << classroom.size() << endl;
            cout << "new class room " << classroom.size() - 1 << "  for course " << i  << " " << endl;
        }
    }
    printf("Case %d: %d\n", ++cnt, classroom.size());
}

int main() {
    //freopen("test.in", "r", stdin);
    //freopen("test.out", "w", stdout);
    scanf("%d", &nCase);
    while (nCase--) {
        //if (++cnt1 == 48) {flag = true;}
        input();
        solve();
    }
    return 0;
}
