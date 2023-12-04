#include "../imports.hpp"
using namespace std;

int main(){
    ifstream fin("day4input.txt");
    string line = "";
    long long ans = 0;
    unordered_map<int, int> mp;
    int ctr = 0;
    while (std::getline(fin, line)){
        ++ctr;
        istringstream iss(line);
        string gbg;
        iss >> gbg >> gbg;
        unordered_set<int> wins;
        iss >> gbg;
        while (gbg != "|"){
            wins.insert(stoi(gbg));
            iss >> gbg;
        }
        int count = 0;
        while (iss >> gbg){
            int val = stoi(gbg);
            if (wins.find(val) != wins.end()){
                ++count;
            }
        }
        mp[ctr] = count;
    }
    queue<int> q;
    for (int i = 1; i <= ctr; ++i){
        q.push(i);
    }
    while (!q.empty()){
        ++ans;
        int val = q.front();
        q.pop();
        if (mp[val] == 0){
            continue;
        }
        for (int i = 1; i <= mp[val]; ++i){
            q.push(val + i);
        }
    }
    cout << ans << endl;
}