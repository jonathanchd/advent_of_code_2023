#include "../imports.hpp"
using namespace std;

#define ll long long

ll partOne(){
    ifstream fin("day5input.txt");
    string line;
    getline(fin, line);
    istringstream iss(line);
    string s;
    iss >> s;
    unordered_set<ll> seeds;
    while (iss >> s){
        seeds.insert(stoll(s));
    }
    unordered_set<ll> converted;
    getline(fin, s);
    for (int i = 0; i < 7; ++i){
        getline(fin, s);
        getline(fin, s); //first numbers
        while (s != ""){
            istringstream is(s);
            string num;
            vector<ll> stuff;
            while (is >> num){
                stuff.push_back(stoll(num));
            }
            ll dest = stuff[0];
            ll source = stuff[1];
            ll length = stuff[2] - 1;
            vector<ll> erased;
            for (ll val : seeds){
                if (val < source || val > source + length){
                    continue;
                }
                erased.push_back(val);
                converted.insert((val - source) + dest);
            }
            for (ll val : erased){
                seeds.erase(val);
            }
            getline(fin, s);
        }
        for (ll val : seeds){
            converted.insert(val);
        }
        seeds = converted;
        converted.clear();
    }
    ll mn = LLONG_MAX;
    for (ll val : seeds){
        mn = min(val, mn);
    }
    return mn;
}

ll partTwo(){
    ifstream fin("day5input.txt");
    string line;
    getline(fin, line);
    istringstream iss(line);
    string s;
    iss >> s;
    set<pair<ll, ll>> seeds;
    while (iss >> s){
        ll start = stoll(s);
        iss >> s;
        ll range = stoll(s);
        seeds.insert({start, start + range - 1});
    }
    set<pair<ll, ll>> converted;
    getline(fin, s);
    for (int i = 0; i < 7; ++i){
        getline(fin, s);
        getline(fin, s); //first numbers
        while (s != ""){
            istringstream is(s);
            string num;
            vector<ll> stuff;
            while (is >> num){
                stuff.push_back(stoll(num));
            }
            ll dest = stuff[0];
            ll source = stuff[1];
            ll length = stuff[2] - 1;
            vector<pair<ll, ll>> erased;
            vector<pair<ll, ll>> added;
            for (auto p : seeds){
                if (p.second < source || p.first > source + length){
                    continue;
                }
                erased.push_back(p);
                //find out how many in the range qualify
                ll end = min(source + length, p.second);
                //everything in the seed range is converted
                converted.insert({p.first - source + dest, end - source + dest});
                if (end != p.second){
                    added.push_back({end + 1, p.second});
                }
            }
            for (auto p : erased){
                seeds.erase(p);
            }
            for (auto p : added){
                seeds.insert(p);
            }
            getline(fin, s);
        }
        for (auto p : seeds){
            converted.insert(p);
        }
        seeds = converted;
        converted.clear();
    }
    ll mn = LLONG_MAX;
    for (auto& p : seeds){
        mn = min(mn, p.first);
    }
    return mn;
}

int main(){
    ll p1 = partOne();
    ll p2 = partTwo();
    cout << "Part one: " << p1 << endl;
    cout << "Part two: " << p2 << endl;
}