#include "../imports.hpp"
using namespace std;

#define ll long long

map<pair<char, pair<int, int>>, pair<int, int>> dir;
unordered_set<char> edges = {'J', 'L', '|', 'S'};
int dr[] = {0, 0, -1, 1};
int dc[] = {-1, 1, 0, 0};

int n, m;

void fillDir(){
    dir[{'F', {-1, 0}}] = {0, 1};
    dir[{'F', {0, -1}}] = {1, 0};
    dir[{'L', {1, 0}}] = {0, 1}; 
    dir[{'L', {0, -1}}] = {-1, 0}; 
    dir[{'J', {0, 1}}] = {-1, 0};
    dir[{'J', {1, 0}}] = {0, -1};
    dir[{'7', {0, 1}}] = {1, 0};
    dir[{'7', {-1, 0}}] = {0, -1};
    dir[{'|', {-1, 0}}] = {-1, 0};
    dir[{'|', {1, 0}}] = {1, 0};
    dir[{'-', {0, -1}}] = {0, -1};
    dir[{'-', {0, 1}}] = {0, 1};
}

bool good(int r, int c){
    return r >= 0 && r < n && c >= 0 && c < m;
}

ll partTwo(){
    ifstream fin("day10input.txt");
    // ifstream fin("day10sample.txt");
    vector<string> v;
    string s;
    pair<int, int> start;
    while (getline(fin, s)){
        v.push_back(s);
        if (s.find('S') != string::npos){
            start = {v.size() - 1, s.find('S')};
        }
    }
    n = v.size();
    m = v[0].size();
    bool found = false;
    pair<int, int> direction = {0, 0};
    set<pair<int, int>> path;
    path.insert(start);
    //top
    if (good(start.first - 1, start.second)){
        char c = v[start.first - 1][start.second];
        if (c == '|' && c == 'F' || c == '7'){
            found = true;
            start = {start.first - 1, start.second};
            direction = {-1, 0};
        }
    }
    //left
    if (!found || good(start.first, start.second - 1)){
        char c = v[start.first][start.second - 1];
        if (c == '-' && c == 'L' || c == 'F'){
            found = true;
            start = {start.first, start.second - 1};
            direction = {0, -1};
        }
    }
    //below
    if (!found || good(start.first + 1, start.second) ){
        char c = v[start.first + 1][start.second];
        if (c == '|' || c == 'L' || c == 'J'){
            found = true;
            start = {start.first + 1, start.second};
            direction = {1, 0};
        }
    }
    //right
    if (!found){
        start = {start.first, start.second + 1};
        char c = v[start.first][start.second + 1];
        direction = {0, 1};
    }
    while (v[start.first][start.second] != 'S'){
        path.insert(start);
        char c = v[start.first][start.second];
        direction = dir[{c, direction}];
        start = {start.first + direction.first, start.second + direction.second};
    }
    ll ret = 0;
    for (int i = 0; i < n; ++i){
        int numIntersections = 0;
        for (int j = 0; j < m; ++j){
            if (path.find({i, j}) != path.end()){
                if (edges.find(v[i][j]) != edges.end()){
                    ++numIntersections;
                }
                continue;
            }
            ret += numIntersections % 2;
        }
    }
    return ret;
}

ll partOne(){
    //floor of pathlength / 2
    ifstream fin("day10input.txt");
    vector<string> v;
    string s;
    pair<int, int> start;
    while (getline(fin, s)){
        v.push_back(s);
        if (s.find('S') != string::npos){
            start = {v.size() - 1, s.find('S')};
        }
    }
    n = v.size();
    m = v[0].size();
    bool found = false;
    pair<int, int> direction = {0, 0};
    //top
    if (good(start.first - 1, start.second)){
        char c = v[start.first - 1][start.second];
        if (c == '|' && c == 'F' || c == '7'){
            found = true;
            start = {start.first - 1, start.second};
            direction = {-1, 0};
        }
    }
    //below
    if (!found || good(start.first + 1, start.second) ){
        char c = v[start.first + 1][start.second];
        if (c == '|' || c == 'L' || c == 'J'){
            found = true;
            start = {start.first + 1, start.second};
            direction = {1, 0};
        }
    }
    //left
    if (!found || good(start.first, start.second - 1)){
        char c = v[start.first][start.second - 1];
        if (c == '-' && c == 'L' || c == 'F'){
            found = true;
            start = {start.first, start.second - 1};
            direction = {0, -1};
        }
    }
    //right
    if (!found){
        start = {start.first, start.second + 1};
        char c = v[start.first][start.second + 1];
        direction = {0, 1};
    }
    ll pathLength = 1;
    while (v[start.first][start.second] != 'S'){
        ++pathLength;
        char c = v[start.first][start.second];
        direction = dir[{c, direction}];
        start = {start.first + direction.first, start.second + direction.second};
    }
    return pathLength / 2;
}

int main(){
    fillDir();
    ll p1 = partOne();
    ll p2 = partTwo();
    cout << "Part one: " << p1 << endl;
    cout << "Part two: " << p2 << endl;
}