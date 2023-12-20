#include "../imports.hpp"
using namespace std;

#define ll long long

struct CompareVector {
    bool operator()(const vector<int>& v1, const vector<int>& v2) {
        return v1[2] < v2[2]; // Comparing based on the third element
    }
};

vector<vector<int>> getInput(const string& filename){
    ifstream fin(filename);
    vector<vector<int>> ret;
    string s;
    while (getline(fin, s)){
        ret.push_back({});
        for (char c : s){
            ret[ret.size() - 1].push_back(c - '0');
        }
    }
    return ret;
}

ll partTwo(){
    const string file = "day17input.txt";
    // const string file = "day17sample.txt";
    return -1;
}

int partOne(){
    const string file = "day17input.txt";
    // const string file = "day17sample.txt";
    vector<vector<int>> v = getInput(file);
    const int n = v.size();
    const int m = v[0].size();
    
    return -1;
}

int main(){
    int p1 = partOne();
    ll p2 = partTwo();
    cout << "Part one: " << p1 << endl;
    cout << "Part two: " << p2 << endl;
}