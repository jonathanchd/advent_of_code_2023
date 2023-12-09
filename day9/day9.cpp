#include "../imports.hpp"
using namespace std;

#define ll long long

bool same(vector<ll>& v){
    for (ll val : v){
        if (val != v[0]){
            return false;
        }
    }
    return true;
}

ll extrapolate(vector<ll> v){
    if (same(v)){
        return v[0];
    }
    vector<ll> next;
    for (int i = 1; i < v.size(); ++i){
        next.push_back(v[i] - v[i - 1]);
    }
    return v[v.size() - 1] + extrapolate(next);
}

ll extrapolate2(vector<ll> v){
    if (same(v)){
        return v[0];
    }
    vector<ll> next;
    for (int i = 1; i < v.size(); ++i){
        next.push_back(v[i] - v[i - 1]);
    }
    return v[0] - extrapolate2(next);
}

ll partTwo(){
    ifstream fin("day9input.txt");
    // ifstream fin("day9sample.txt");
    string s;
    ll ret = 0;
    while (getline(fin, s)){
        istringstream iss(s);
        vector<ll> v;
        while (iss >> s){
            v.push_back(stoll(s));
        }
        ret += extrapolate2(v);
    }
    return ret;
}

ll partOne(){
    ifstream fin("day9input.txt");
    // ifstream fin("day9sample.txt");
    string s;
    ll ret = 0;
    while (getline(fin, s)){
        istringstream iss(s);
        vector<ll> v;
        while (iss >> s){
            v.push_back(stoll(s));
        }
        ret += extrapolate(v);
    }
    return ret;
}

int main(){
    ll p1 = partOne();
    cout << "Part one: " << p1 << endl;
    ll p2 = partTwo();
    cout << "Part two: " << p2 << endl;
}