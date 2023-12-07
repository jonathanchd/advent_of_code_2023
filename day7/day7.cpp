#include "../imports.hpp"
using namespace std;

#define ll long long

unordered_map<char, int> ranks = {{'2', 0}, {'3', 1}, {'4', 2}, {'5', 3},
                                {'6', 4}, {'7', 5}, {'8', 6}, {'9', 7}, {'T', 8}, {'J', 9},
                                {'Q', 10}, {'K', 11}, {'A', 12}};

int handRank(const string& s){
    unordered_map<char, int> mp;
    for (char c : s){
        ++mp[c];
    }
    if (mp.size() == 5){
        return 0; //high card
    }
    if (mp.size() == 4){
        return 1; //pair
    }
    if (mp.size() == 3){
        for (auto& p : mp){
            if (p.second == 3){
                return 3; //three of a kind
            }
        }
        return 2; //2 pair
    }
    if (mp.size() == 2){
        for (auto& p : mp){
            if (p.second == 3){
                return 4; //full house
            }
            if (p.second == 4){
                return 5; //four of a kind;
            }
        }
    }
    return 6; //five of a kind
}

bool handCMP(const pair<string, ll>& a, const pair<string, ll>& b){
    int rankA = handRank(a.first);
    int rankB = handRank(b.first);
    if (rankA != rankB){
        return rankA < rankB;
    }
    for (int i = 0; i < 5; ++i){
        if (ranks[a.first[i]] == ranks[b.first[i]]){
            continue;
        }
        return ranks[a.first[i]] < ranks[b.first[i]];
    }
    return false;
}

string jokerHand(string s){
    int jokerCount = 0;
    unordered_map<char, int> mp;
    for (char c : s){
        if (c == 'J'){
            ++jokerCount;
        }
        else{
            ++mp[c];
        }
    }
    if (jokerCount == 0){
        return s;
    }
    if (jokerCount == 5){
        return "AAAAA";
    }
    if (jokerCount == 4){
        char c = mp.begin()->first;
        return string(5, c);
    }
    char highest = mp.begin()->first;
    for (auto& p : mp){
        if (p.second > mp[highest]){
            highest = p.first;
        }
        else if (p.second == mp[highest] && ranks[p.first] > ranks[highest]){
            highest = p.first;
        }
    }
    for (int i = 0; i < 5; ++i){
        if (s[i] == 'J'){
            s[i] = highest;
        }
    }
    return s;
}

bool jokerCMP(const pair<string, ll>& a, const pair<string, ll>& b){
    int ra = handRank(jokerHand(a.first));
    int rb = handRank(jokerHand(b.first));
    if (ra != rb){
        return ra < rb;
    }
    for (int i = 0; i < 5; ++i){
        if (ranks[a.first[i]] == ranks[b.first[i]]){
            continue;
        }
        return ranks[a.first[i]] < ranks[b.first[i]];
    }
    return false;
}

ll partTwo(){
    ranks['J'] = -1;
    ifstream fin("day7input.txt");
    // ifstream fin("day7sample.txt");
    vector<pair<string, ll>> v;
    string hand;
    ll bid;
    while (fin >> hand >> bid){
        v.push_back({hand, bid});
    }
    sort(v.begin(), v.end(), jokerCMP);
    ll ans = 0;
    cout << endl;
    for (int i = 0; i < v.size(); ++i){
        cout << v[i].first << endl;
        ans += (i + 1) * v[i].second;
    }
    return ans;
}

ll partOne(){
    ifstream fin("day7input.txt");
    // ifstream fin("day7sample.txt");
    vector<pair<string, ll>> v;
    string hand;
    ll bid;
    while (fin >> hand >> bid){
        v.push_back({hand, bid});
    }
    sort(v.begin(), v.end(), handCMP);
    ll ans = 0;
    for (int i = 0; i < v.size(); ++i){
        ans += (i + 1) * v[i].second;
    }
    return ans;
}

int main(){
    ll p1 = partOne();
    ll p2 = partTwo();
    cout << "Part one: " << p1 << endl;
    cout << "Part two: " << p2 << endl;
}