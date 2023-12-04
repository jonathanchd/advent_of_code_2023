#include "../imports.hpp"
using namespace std;

vector<vector<int>> delta = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, 
    {0, 1}, {1, -1}, {1, 0}, {1, 1}};

bool good(int r, int c, int n, int m, const vector<string>& v){
    return r >= 0 && c >= 0 && r < n && c < m && v[r][c] != '.' && !isalnum(v[r][c]);
}

long long partTwo(vector<string>& v){
    map<pair<int, int>, vector<int>> mp;
    int n = v.size();
    int m = v[0].size();
    string s;
    long long ret = 0;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            if (v[i][j] < '0' || v[i][j] > '9'){
                continue;
            }
            //found a number
            set<pair<int, int>> symbols;
            for (int k = 0; k < delta.size(); ++k){
                if (good(i + delta[k][0], j + delta[k][1], n, m, v)){
                    symbols.insert({i + delta[k][0], j + delta[k][1]});
                }
            }
            s = v[i][j];
            while (j + 1 < m && v[i][j + 1] >= '0' && v[i][j + 1] <= '9'){
                ++j;
                s += v[i][j];
                for (int k = 0; k < delta.size(); ++k){
                    if (good(i + delta[k][0], j + delta[k][1], n, m, v)){
                        symbols.insert({i + delta[k][0], j + delta[k][1]});
                    }
                }
            }
            if (symbols.size() != 0){
                int val = stoi(s);
                for (auto& p : symbols){
                    mp[p].push_back(val);
                }
            }
        }
    }
    for (auto& p : mp){
        if (p.second.size() != 2){
            continue;
        }
        ret += p.second[0] * p.second[1];
    }
    return ret;
}

int main(){
    ifstream fin("day3input.txt");
    string s;
    long long ans = 0;
    long long anspt2 = 0;
    vector<string> v;
    while (fin >> s){
        v.push_back(s);
    }
    int n = v.size();
    int m = v[0].size();
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            if (v[i][j] < '0' || v[i][j] > '9'){
                continue;
            }
            //found a number
            bool symbolNear = false;
            for (int k = 0; k < delta.size(); ++k){
                if (good(i + delta[k][0], j + delta[k][1], n, m, v)){
                    symbolNear = true;
                    break;
                }
            }
            s = v[i][j];
            while (j + 1 < m && v[i][j + 1] >= '0' && v[i][j + 1] <= '9'){
                ++j;
                s += v[i][j];
                if (!symbolNear){
                    for (int k = 0; k < delta.size(); ++k){
                        if (good(i + delta[k][0], j + delta[k][1], n, m, v)){
                            symbolNear = true;
                            break;
                        }
                    }
                }
            }
            if (symbolNear){
                ans += stoi(s);
            }
        }
    }
    anspt2 = partTwo(v);
    cout << ans << endl << anspt2 << endl;
}