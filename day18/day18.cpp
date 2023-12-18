#include "../imports.hpp"
using namespace std;

#define ll long long

ll partTwo(){
    unordered_map<int, pair<int, int>> mp = {{0, {1, 0}}, {2, {-1, 0}}, 
                                                {3, {0, 1}}, {1, {0, -1}}};
    // ifstream fin("day18sample.txt");
    ifstream fin("day18input.txt");
    string s;
    vector<string> instructions;
    int currX = 0, currY = 0;
    vector<pair<ll, ll>> v;
    ll perim = 0;
    while (getline(fin, s)){
        v.push_back({currX, currY});
        istringstream iss(s);
        string hex;
        iss >> hex >> hex >> hex; //we want the last one
        int dir = stoi(hex.substr(7, 1));
        int magnitude = stoi(hex.substr(2, 5), 0, 16);
        perim += magnitude;
        const pair<int, int>& p = mp[dir];
        currX += p.first * magnitude;
        currY += p.second * magnitude;
    }
    int n = v.size();
    ll area = 0;
    for (int i = 0; i < n; ++i){
        int j = (i + 1) % n;
        area += (v[i].first * v[j].second) - (v[j].first * v[i].second);
    }
    return (abs(area) / 2) + (perim / 2) + 1;
}

ll partOne(){
    unordered_map<string, pair<int, int>> mp = {{"R", {1, 0}}, {"L", {-1, 0}}, 
                                                {"U", {0, 1}}, {"D", {0, -1}}};
    // ifstream fin("day18sample.txt");
    ifstream fin("day18input.txt");
    vector<pair<ll, ll>> v;
    int currX = 0, currY = 0;
    string s;
    ll perim = 0;
    while (getline(fin, s)){
        v.push_back({currX, currY});
        istringstream iss(s);
        string dir, mag, color;
        iss >> dir >> mag >> color;
        const pair<ll, ll>& p = mp[dir];
        int magnitude = stoi(mag);
        currX += p.first * magnitude;
        currY += p.second * magnitude;
        perim += magnitude;
    }
    int n = v.size();
    ll area = 0;
    for (int i = 0; i < n; ++i){
        int j = (i + 1) % n;
        area += (v[i].first * v[j].second) - (v[j].first * v[i].second);
    }
    return (abs(area) / 2) + (perim / 2) + 1;
}

int main(){
    ll p1 = partOne();
    ll p2 = partTwo();
    cout << "Part one: " << p1 << endl;
    cout << "Part two: " << p2 << endl;
}