#include "../imports.hpp"
using namespace std;

#define ll long long

struct hashFunction{ 
  size_t operator()(const pair<int, int> &x) const{ 
    return x.first ^ x.second; 
  } 
}; 

int dr[] = {0, 0, -1, 1};
int dc[] = {-1, 1, 0, 0};

int indexOf(const string& s, char c){
    for (int i = 0; i < s.length(); ++i){
        if (s[i] == c){
            return i;
        }
    }
    return -1;
}

//returns a % b, if a is negative, add b til A is positive
ll mod(ll a, ll b){
    ll ret = a % b;
    while (ret < 0){
        ret += b;
    }
    return ret;
}

bool good(int r, int c, int n, int m){
    return r >= 0 && r < n && c >= 0 && c < m;
}

ll partTwo(){
    // ifstream fin("day21input.txt");
    ifstream fin("day21sample.txt");
    vector<string> v;
    string s;
    pair<int, int> start;
    while (getline(fin, s)){
        v.push_back(s);
        int index = indexOf(s, 'S');
        if (index != -1){
            start.first = v.size() - 1;
            start.second = index;
        }
    }
    queue<vector<int>> q;
    const int n = v.size();
    const int m = v[0].size();
    int thresh = 500;
    q.push({start.first, start.second, 0});
    unordered_set<pair<int, int>, hashFunction> visited;
    visited.insert(start);
    unordered_set<pair<int, int>, hashFunction> st;
    while (!q.empty()){
        vector<int> curr = q.front();
        q.pop();
        if (curr[2] % 2 == thresh % 2 || curr[2] == thresh){
            st.insert({curr[0], curr[1]});
        }
        if (curr[2] == thresh){
            continue;
        }
        for (int i = 0; i < 4; ++i){
            int nr = curr[0] + dr[i];
            int nc = curr[1] + dc[i];
            ll modR = mod(nr, n);
            ll modC = mod(nc, m);
            if (v[modR][modC] == '#' || visited.find({nr, nc}) != visited.end()){
                continue;
            }
            visited.insert({nr, nc});
            q.push({nr, nc, curr[2] + 1});
        }
    }
    return st.size();
}

ll partOne(){
    ifstream fin("day21input.txt");
    // ifstream fin("day21sample.txt");
    vector<string> v;
    string s;
    pair<int, int> start;
    while (getline(fin, s)){
        v.push_back(s);
        int index = indexOf(s, 'S');
        if (index != -1){
            start.first = v.size() - 1;
            start.second = index;
        }
    }
    queue<vector<int>> q;
    const int n = v.size();
    const int m = v[0].size();
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    visited[start.first][start.second] = true;
    int thresh = 64;
    q.push({start.first, start.second, 0});
    unordered_set<pair<int, int>, hashFunction> st;
    while (!q.empty()){
        vector<int> curr = q.front();
        q.pop();
        if (curr[2] % 2 == 0 || curr[2] == thresh){
            st.insert({curr[0], curr[1]});
        }
        if (curr[2] == thresh){
            continue;
        }
        for (int i = 0; i < 4; ++i){
            int nr = curr[0] + dr[i];
            int nc = curr[1] + dc[i];
            if (!good(nr, nc, n, m) || v[nr][nc] == '#' || visited[nr][nc]){
                continue;
            }
            visited[nr][nc] = true;
            q.push({nr, nc, curr[2] + 1});
        }
    }
    return st.size();
}

int main(){
    ll p1 = partOne();
    ll p2 = partTwo();
    cout << "Part one: " << p1 << endl;
    cout << "Part two: " << p2 << endl;
}