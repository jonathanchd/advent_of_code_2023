#include "../imports.hpp"
using namespace std;

#define ll long long

ll partTwo(){
    ifstream fin("day6input.txt");
    // ifstream fin("day6sample.txt");
    vector<ll> times, distances;
    string line;
    getline(fin, line);
    string t = "";
    string d = "";
    string a, b;
    while (fin >> a >> b){
        t += a;
        d += b;
    }
    double time = stod(t);
    double distance = stod(d);
    //distance for any time i is (i * (time - i))
    double start = (-time + sqrt((time * time) - (4 * distance))) / (-2);
    double end = (-time - sqrt((time * time) - (4 * distance))) / (-2);
    ll st = (ll)ceil(start);
    ll en = (ll)end;
    return en - st + 1;
}

ll p1helper(ll time, ll distance){
    ll ret = 0;
    for (int i = 1; i < time; ++i){
        if (i * (time - i) > distance){
            ++ret;
        }
    }
    return ret;
}

ll partOne(){
    ifstream fin("day6input.txt");
    //ifstream fin("day6sample.txt");
    vector<ll> times, distances;
    string line;
    getline(fin, line);
    while (getline(fin, line)){
        istringstream iss(line);
        string time, distance;
        iss >> time >> distance;
        times.push_back(stoll(time));
        distances.push_back(stoll(distance));
    }
    ll ans = 1;
    for (int i = 0; i < times.size(); ++i){
        ans *= p1helper(times[i], distances[i]);
    }
    return ans;
}

int main(){
    ll p1 = partOne();
    ll p2 = partTwo();
    cout << "Part one: " << p1 << endl;
    cout << "Part two: " << p2 << endl;
}