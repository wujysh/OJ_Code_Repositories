/*
#include <algorithm>
//#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
using namespace std;

const int MAXN = 10010;
int n;
char name[MAXN][40];

struct Time {
    int year, month, day, hour, minute, second;
    Time() {year = month = day = hour = minute = second = 0;}
    Time(int _year, int _month, int _day, int _hour, int _minute, int _second) : year(_year), month(_month), day(_day), hour(_hour), minute(_minute), second(_second) {}
    bool operator<(const Time t2) const {
        if (year != t2.year) return year < t2.year;
        if (month != t2.month) return month < t2.month;
        if (day != t2.day) return day < t2.day;
        if (hour != t2.hour) return hour < t2.hour;
        if (minute != t2.minute) return minute < t2.minute;
        return second < t2.second;
    }
};

struct Operation {
    Time time;
    int programmer, type, line;  // type: 0-sync, 1-modify, 2-submit;
    Operation() {}
    Operation(Time _time, int _programmer, int _type, int _line) : time(_time), programmer(_programmer), type(_type), line(_line) {}
    bool operator<(const Operation op2) const {
        return time < op2.time;
    }
};
vector<Operation> operations;

struct Programmer {
    //string name;
    char *name;
    int priority;
    Programmer() {}
    //Programmer(string _name, int _priority) : name(_name), priority(_priority) {}
    Programmer(char *_name, int _priority) : name(_name), priority(_priority) {}
};
vector<Programmer> programmers;

struct Line {
    bool edited;
    Time time;
    int programmer, priority;
    Line() {edited = false;}
    Line(Time _time, int _programmer, int _priority) : edited(false), time(_time), programmer(_programmer), priority(_priority) {}
};
//map<int, Line> lines;
vector<Line> lines;

struct Process {
    set<int> lines;
    Time sync_time, modify_time, submit_time;
    Process() {}
    Process(Time _sync, Time _modify, Time _submit) : sync_time(_sync), modify_time(_modify), submit_time(_submit) {}
};
map<int, Process> process;

void init() {
    operations.clear();
    programmers.clear();
    lines.clear();
    lines.resize(250);
    process.clear();
}

void input() {
    for (int i = 0; i < n; i++) {
        //string name;
        int priority, op;
        //cin >> name >> priority >> op;
        scanf("%s%d%d", name[i], &priority, &op);
        programmers.push_back(Programmer(name[i], priority));
        for (int j = 0; j < op; j++) {
            int year, month, day, hour, minute, second, line = 0;
            char type[10];
            int _type;
            //cin.ignore();
            scanf(" [%d/%d/%d %d:%d:%d] %s", &year, &month, &day, &hour, &minute, &second, type);
            //cin >> type;
            //cout << year << month << day << hour << minute << second << type << endl;
            if (type[0] == 'S') {
                _type = 0;
                line = -1;
            }
            if (type[0] == 'M') {
                _type = 1;
                scanf("%d", &line);
                //while (cin >> line && line > 230);
            }
            if (type[0] == 'S') {
                _type = 2;
                line = -1;
            }
            //cout << "line:" << line << endl;
            operations.push_back(Operation(Time(year, month, day, hour, minute, second), i, _type, line));
        }
        //cout << "!!!" << endl;
    }
}

void work() {
    sort(operations.begin(), operations.end());
    for (int i = 0; i < operations.size(); i++) {
        Operation op = operations[i];
        //cout << op.programmer << " " << op.type << " " << op.line << endl;
        //if (op.line >= lines.size()) {
        //    lines.resize(250);
        //}
        if (op.type == 0) {  // SYNC
            process[op.programmer] = Process(op.time, Time(), Time());
            process[op.programmer].lines.clear();
        }
        if (op.type == 1) {  // MODIFY
            process[op.programmer].modify_time = op.time;
            if (op.line != -1) {
                process[op.programmer].lines.insert(op.line);
            }
        }
        if (op.type == 2) {  // SUBMIT
            process[op.programmer].submit_time = op.time;

            //for (int j = 0; j < process[op.programmer].lines.size(); j++) {
            //    int line = process[op.programmer].lines[j];
            set<int>::iterator it;
            for (it = process[op.programmer].lines.begin(); it != process[op.programmer].lines.end(); it++) {
                int line = *it;
                //cout << op.programmer << " " << op.line << endl;
                //Time t = lines[line].time;
                //printf("[%04d/%02d/%02d %02d:%02d:%02d] ", t.year, t.month, t.day, t.hour, t.minute, t.second);
                //t = process[op.programmer].sync_time;
                //printf("[%04d/%02d/%02d %02d:%02d:%02d] ", t.year, t.month, t.day, t.hour, t.minute, t.second);
                //cout << lines[line].programmer << endl;
                ///if (line >= lines.size()) continue;

                if (lines[line].time < process[op.programmer].sync_time) {
                    lines[line].time = process[op.programmer].submit_time;
                    lines[line].programmer = op.programmer;
                    //cout << op.programmer << endl;
                    lines[line].priority = programmers[op.programmer].priority;//process[op.programmer][op.line].priority;
                    lines[line].edited = true;
                    //erase(process[op.programmer][op.line]);
                } else if (programmers[op.programmer].priority > lines[line].priority) {
                    lines[line].time = process[op.programmer].submit_time;
                    lines[line].programmer = op.programmer;
                    //cout << op.programmer << endl;
                    lines[line].priority = programmers[op.programmer].priority;//process[op.programmer][op.line].priority;
                    lines[line].edited = true;
                    //process[op.programmer][op.line].erase();
                }
            }

            process[op.programmer].sync_time = op.time;
        }
    }
}

void output() {
    for (int i = 1; i < lines.size(); i++) {
        if (lines[i].edited) {
            //cout << i << " ";
            Time t = lines[i].time;
            //printf("[%04d/%02d/%02d %02d:%02d:%02d] BY ", t.year, t.month, t.day, t.hour, t.minute, t.second);
            //cout << programmers[lines[i].programmer].name << endl;
            printf("%d [%04d/%02d/%02d %02d:%02d:%02d] BY %s\n", i, t.year, t.month, t.day, t.hour, t.minute, t.second, programmers[lines[i].programmer].name);
        }
    }
    //cout << "END" << endl;
    printf("END\n");
}

int main() {
    //ios::sync_with_stdio(false);
    //freopen("out.txt", "w", stdout);
    while (scanf("%d", &n), n) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>

using namespace std;

const int MAXN = 10010;

map<int,int> mp;

struct OP
{
    int id,pr,kind,line;
    int yy,mm,dd,h,m,s;
    char str[10];
    long long time;
    void read(int _id,int _pr)
    {
        id = _id;
        pr = _pr;
        scanf(" [%d/%d/%d %d:%d:%d] %s",&yy,&mm,&dd,&h,&m,&s,str);
        if(str[0]=='M')
        {
            kind = 2;
            scanf("%d",&line);
            mp[line] = -1;
        }
        else
        {
            if(str[1]=='Y')kind = 1;
            else kind = 3;
        }
        time = s + m*60 + h*3600 + dd*3600*24 + mm*3600*24*31 + yy*(long long)3600*24*31*366;
    }
    void print()
    {
        printf("%d [%04d/%02d/%02d %02d:%02d:%02d] %d\n",id,yy,mm,dd,h,m,s,kind);
    }
    bool operator<(const OP &B)const
    {
        return time<B.time;
    }
};

char name[MAXN][40];
vector<int>MV[MAXN];
OP op[MAXN*5];
long long get[MAXN];

int main()
{
    //freopen("in","r",stdin);
    int n;
    while(scanf("%d",&n),n)
    {
        int pr,m;
        int tot = 0;
        mp.clear();
        for(int i=1;i<=n;i++)
        {
            scanf("%s%d%d",&name[i],&pr,&m);
            MV[i].clear();
            for(int j=0;j<m;j++)
                op[tot++].read(i,pr);
        }
        sort(op,op+tot);
        for(int i=0;i<tot;i++)
        {
            //op[i].print();
            int id = op[i].id;
            if(op[i].kind==1)get[id] = op[i].time;
            else if(op[i].kind==2)MV[id].push_back(op[i].line);
            else
            {
                for(int j=0;j<MV[id].size();j++)
                {
                    int line = MV[id][j];
                    long long last = mp[line]==-1?-1:op[mp[line]].time;
                    if(last<get[id])mp[line] = i;
                    else if(op[mp[line]].pr<op[i].pr)mp[line] = i;
                }
                MV[id].clear();
                get[id] = op[i].time;
            }
        }
        for(map<int,int>::iterator it = mp.begin();it!=mp.end();it++)
        {
            if(it->second==-1)continue;//
            int id = it->second;
            printf("%d [%04d/%02d/%02d %02d:%02d:%02d] BY %s\n",it->first,op[id].yy,op[id].mm,op[id].dd,op[id].h,op[id].m,op[id].s,name[op[id].id]);
        }
        puts("END");
    }
    return 0;
}
