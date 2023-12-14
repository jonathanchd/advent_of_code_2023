#include "../imports.hpp"
using namespace std;

#define ll long long

void rotateClockwise(vector<string>& v){
    vector<string> rotated(v[0].size(), string(v.size(), 'a'));
    for (int i = 0; i < v.size(); ++i){
        for (int j = 0; j < v[0].size(); ++j){
            rotated[j][v.size() - i - 1] = v[i][j];
        }
    }
    v = rotated;
}

void applyUpwardGravity(vector<string>& v){
    const int rows = v.size();
    const int cols = v[0].size();
    for (int col = 0; col < cols; ++col){
        int row = rows - 1;
        int count = 0;
        while (row >= 0){
            if (v[row][col] == 'O'){
                ++count;
                v[row][col] = '.';
            }
            else if (v[row][col] == '#' && count != 0){
                for (int i = 1; i <= count; ++i){
                    v[row + i][col] = 'O';
                }
                count = 0;
            }
            --row;
        }
        if (count != 0){
            for (int i = 0; i < count; ++i){
                v[i][col] = 'O';
            }
        }
    }
}

void printVector(const vector<string>& v){
    for (const string& s : v){
        cout << s << endl;
    }
}

//does one cycle of north west south east
void cycle(vector<string>& v){
    for (int i = 0; i < 4; ++i){
        applyUpwardGravity(v);
        rotateClockwise(v);
    }
}

string toString(const vector<string>& v){
    string ret = "";
    for (const string& s : v){
        ret += s;
    }
    return ret;
}

ll countWeight(const vector<string>& v){
    ll ans = 0;
    const int n = v.size();
    const int m = v[0].size();
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            if (v[i][j] == 'O'){
                ans += n - i;
            }
        }
    }
    return ans;
}

ll partTwo(){
    ifstream fin("day14input.txt");
    // ifstream fin("day14sample.txt");
    vector<string> v;
    string s;
    while (getline(fin, s)){
        v.push_back(s);
    }
    const int numCycles = 1000000000;
    unordered_map<string, int> cycles;
    vector<vector<string>> stuff;
    cycles[toString(v)] = 0;
    stuff.push_back(v);
    for (int i = 1; i <= numCycles; ++i){
        cycle(v);
        string key = toString(v);
        stuff.push_back(v);
        if (cycles.find(key) == cycles.end()){
            cycles[key] = i;
        }
        else{
            int firstInstance = cycles[key];
            int cycleLength = i - firstInstance;
            int cyclesRemaining = numCycles - (i);
            int mod = cyclesRemaining % cycleLength;
            return countWeight(stuff[firstInstance + mod]);
        }
    }
    return countWeight(v);
}

ll partOne(){
    ifstream fin("day14input.txt");
    // ifstream fin("day14sample.txt");
    vector<string> v;
    string s;
    while (getline(fin, s)){
        v.push_back(s);
    }
    ll ans = 0;
    const int n = v.size();
    const int m = v[0].size();
    for (int col = 0; col < m; ++col){
        int row = n - 1;
        int count = 0; //number of O's
        while (row >= 0){
            if (v[row][col] == 'O'){
                ++count;
            }
            if (v[row][col] == '#' && count != 0){
                for (int i = 1; i <= count; ++i){
                    ans += n - (row + i);
                }
                count = 0;
            }
            --row;
        }
        if (count != 0){
            for (int i = 0; i < count; ++i){
                ans += n - i;
            }
        }
    }
    return ans;
}

int main(){
    ll p1 = partOne();
    ll p2 = partTwo();
    cout << "Part one: " << p1 << endl;
    cout << "Part two: " << p2 << endl;
}