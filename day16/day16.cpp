#include "../imports.hpp"
using namespace std;

#define ll long long

map<pair<char, pair<int, int>>, pair<int, int>> mp;

void fillMap(){
    mp[{'/', {0, 1}}] = {-1, 0};
    mp[{'/', {0, -1}}] = {1, 0};
    mp[{'/', {1, 0}}] = {0, -1};
    mp[{'/', {-1, 0}}] = {0, 1};
    mp[{'\\', {0, 1}}] = {1, 0};
    mp[{'\\', {0, -1}}] = {-1, 0};
    mp[{'\\', {1, 0}}] = {0, 1};
    mp[{'\\', {-1, 0}}] = {0, -1};
}

vector<string> getInput(const string& filename){
    vector<string> v;
    ifstream fin(filename);
    string s;
    while (getline(fin, s)){
        v.push_back(s);
    }
    return v;
}

ll simulate(vector<string>& v, int startR, int startC, int srDir, int scDir){
    const int n = v.size();
    const int m = v[0].size();
    vector<vector<int>> energy(n, vector<int>(m, 0));
    //vector of row, col, rDir, cDir
    queue<vector<int>> q;
    q.push({startR, startC, srDir, scDir});
    map<pair<int, int>, set<pair<int, int>>> visited;
    while (!q.empty()){
        vector<int> curr = q.front();
        q.pop();
        int r = curr[0];
        int c = curr[1];
        int rDir = curr[2];
        int cDir = curr[3];
        pair<int, int> pos = {r, c};
        if (visited[pos].find({rDir, cDir}) != visited[pos].end()){
            continue;
        }
        visited[pos].insert({rDir, cDir});
        if (r < 0 || c < 0 || r >= n || c >= m){
            continue;
        }
        energy[r][c] = 1;
        if (v[r][c] == '.' || (v[r][c] == '-' && cDir != 0) || (v[r][c] == '|' && rDir != 0)){
            q.push({r + rDir, c + cDir, rDir, cDir});
        }
        else if (v[r][c] == '-' && rDir != 0){
            q.push({r, c - 1, 0, -1});
            q.push({r, c + 1, 0, 1});
        }
        else if (v[r][c] == '|' && cDir != 0){
            q.push({r + 1, c, 1, 0});
            q.push({r - 1, c, -1, 0});
        }
        else{
            pair<int, int> dir = mp[{v[r][c], {rDir, cDir}}];
            q.push({r + dir.first, c + dir.second, dir.first, dir.second});
        }
    }
    ll tot = 0;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            tot += energy[i][j];
        }
    }
    return tot;
}

ll partTwo(){
    vector<string> v = getInput("day16input.txt");
    ll ans = 0;
    for (int i = 0; i < v.size(); ++i){
        ans = max(ans, simulate(v, i, 0, 0, 1));
        ans = max(ans, simulate(v, i, v[0].size() - 1, 0, -1));
    }
    for (int i = 0; i < v[0].size(); ++i){
        ans = max(ans, simulate(v, 0, i, 1, 0));
        ans = max(ans, simulate(v, v.size() - 1, i, -1, 0));
    }
    return ans;
}

ll partOne(){
    vector<string> v = getInput("day16input.txt");
    return simulate(v, 0, 0, 0, 1);
}

int main(){
    fillMap();
    ll p1 = partOne();
    ll p2 = partTwo();
    cout << "Part one: " << p1 << endl;
    cout << "Part two: " << p2 << endl;
}