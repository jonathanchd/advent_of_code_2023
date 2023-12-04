#include "../imports.hpp"
#include <sstream>
using namespace std;


int partTwo(const string& s, unordered_map<string, int>& mp){
    int first = -1, last = -1;
    for (int i = 0; i < s.length(); ++i){
        if (s[i] >= '0' && s[i] <= '9'){
            if (first == -1){
                first = s[i] - '0';
            }
            last = s[i] - '0';
            continue;
        }
        if (i <= s.length() - 3){
            string sub = s.substr(i, 3);
            if (mp.count(sub)){
                if (first == -1){
                    first = mp[sub];
                }
                last = mp[sub];
            }
        }
        if (i <= s.length() - 4){
            string sub = s.substr(i, 4);
            if (mp.count(sub)){
                if (first == -1){
                    first = mp[sub];
                }
                last = mp[sub];
            }
        }
        if (i <= s.length() - 5){
            string sub = s.substr(i, 5);
            if (mp.count(sub)){
                if (first == -1){
                    first = mp[sub];
                }
                last = mp[sub];
            }
        }
    }
    return first * 10 + last;
}

int main(){
    ifstream fin("day1input.txt");
    string s;
    long long ans = 0;
    long long anspt2 = 0;
    unordered_map<string, int> mp;
    mp["one"] = 1;
    mp["two"] = 2;;
    mp["three"] = 3;
    mp["four"] = 4;
    mp["five"] = 5;
    mp["six"] = 6;
    mp["seven"] = 7;
    mp["eight"] = 8;
    mp["nine"] = 9;
    while (fin >> s){
        int first = -1, last = -1;
        for (char c : s){
            if (c < '0' || c > '9'){
                continue;
            }
            if (first == -1){
                first = c - '0';
            }
            last = c - '0';
        }
        ans += first * 10 + last;
        anspt2 += partTwo(s, mp);
    }
    cout << ans << endl << anspt2 << endl;
}