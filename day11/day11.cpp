#include "../imports.hpp"
using namespace std;

#define ll long long

ll helper(int expansion){
    ifstream fin("day11input.txt");
    //ifstream fin("day11sample.txt");
    string s;
    vector<string> v;
    while (getline(fin, s)){
        v.push_back(s);
    }
    vector<pair<int, int>> galaxies;
    int n = v.size();
    int m = v[0].size();
    vector<int> emptyCols, emptyRows;
    for (int i = 0; i < n; ++i){
        bool empty = true;
        for (int j = 0; j < m; ++j){
            if (v[i][j] == '#'){
                galaxies.push_back({i, j});
                empty = false;
            }
        }
        if (empty){
            emptyRows.push_back(i);
        }
    }
    for (int i = 0; i < m; ++i){
        bool empty = true;
        for (int j = 0; j < n; ++j){
            if (v[j][i] == '#'){
                empty = false;
                break;
            }
        }
        if (empty){
            emptyCols.push_back(i);
        }
    }
    ll ans = 0;
    for (int i = 0; i < galaxies.size(); ++i){
        for (int j = i + 1; j < galaxies.size(); ++j){
            int r1 = galaxies[i].first, c1 = galaxies[i].second;
            int r2 = galaxies[j].first, c2 = galaxies[j].second;
            ans += abs(r1 - r2) + abs(c1 - c2);
            for (int val : emptyRows){
                if (val > min(r1, r2) && val < max(r1, r2)){
                    ans += expansion - 1;
                }
            }
            for (int val : emptyCols){
                if (val > min(c1, c2) && val < max(c1, c2)){
                    ans += expansion - 1;
                }
            }
        }
    }
    return ans;
}

ll partTwo(){
    return helper(1000000);
}

ll partOne(){
    return helper(2);
}

int main(){
    ll p1 = partOne();
    ll p2 = partTwo();
    cout << "Part one: " << p1 << endl;
    cout << "Part two: " << p2 << endl;
}