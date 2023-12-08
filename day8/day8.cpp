#include "../imports.hpp"
using namespace std;

#define ll long long

int timeTaken(string& inst, unordered_map<string, pair<string, string>>& mp, string& curr){
    int ptr = 0;
    int time = 0;
    while (true){
        ++time;
        if (inst[ptr] == 'R'){
            curr = mp[curr].second;
        }
        else{
            curr = mp[curr].first;
        }
        if (curr[2] == 'Z'){
            return time;
        }
        ptr = (ptr + 1) % inst.length();
    }
}

ll gcd(ll a, ll b) {
    while (b != 0) {
        ll temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

ll lcm(ll a, ll b) {
    // LCM * GCD = |a * b|
    return (a * b) / gcd(a, b);
}

ll partTwo(){
    ifstream fin("day8input.txt");
    string inst;
    fin >> inst;
    unordered_map<string, pair<string, string>> mp;
    string a, b, c;
    vector<string> currs;
    while (fin >> a >> b >> c){
        if (a[2] == 'A'){
            currs.push_back(a);
        }
        mp[a] = {b.substr(0, b.length() - 1), c};
    }
    vector<ll> times;
    for (string& curr : currs){
        times.push_back(timeTaken(inst, mp, curr));
    }
    ll ans = times[0];
    for (int i = 1; i < times.size(); ++i){
        ans = lcm(ans, times[i]);
    }
    return ans;
    
}

ll partOne(){
    ifstream fin("day8input.txt");
    string inst;
    fin >> inst;
    unordered_map<string, pair<string, string>> mp;
    string a, b, c;
    while (fin >> a >> b >> c){
        mp[a] = {b.substr(0, b.length() - 1), c};
    }
    ll ans = 0;
    int ptr = 0;
    string curr = "AAA";
    while (true){
        ++ans;
        if (inst[ptr] == 'R'){
            curr = mp[curr].second;
        }
        else{
            curr = mp[curr].first;
        }
        if (curr == "ZZZ"){
            return ans;
        }
        ptr = (ptr + 1) % inst.length();
    }
    return ans;
}

int main(){
    ll p1 = partOne();
    ll p2 = partTwo();
    cout << "Part one: " << p1 << endl;
    cout << "Part two: " << p2 << endl;
}