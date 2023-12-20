#include "../imports.hpp"
using namespace std;

#define ll long long

int indexOf(const string& s, char c);

unordered_map<char, int> mappings = {{'x', 0}, {'m', 1}, {'a', 2}, {'s', 3}};

class Cmp{
public:
    Cmp(const string& input){
        index = mappings[input[0]];
        greaterThan = indexOf(input, '>') != -1;
        int sign = greaterThan ? indexOf(input, '>') : indexOf(input, '<');
        threshold = stoi(input.substr(sign + 1, input.length() - sign - 1));
    }
    bool operator()(const vector<int>& v){
        if (greaterThan){
            return v[index] > threshold;
        }
        return v[index] < threshold;
    }
    int getThreshold(){
        return threshold;
    }
    int getIndex(){
        return index;
    }
    bool getGT(){
        return greaterThan;
    }
private:
    int threshold, index;
    bool greaterThan;
};


int indexOf(const string& s, char c){
    for (int i = 0; i < s.length(); ++i){
        if (s[i] == c){
            return i;
        }
    }
    return -1;
}

pair<Cmp, string> createProcess(const string& process){
    int colon = indexOf(process, ':');
    //edge case where it just sends to a default process at the end
    if (colon == -1){
        Cmp c("x>" +to_string(INT_MIN));
        return {c, process};
    }
    string exp = process.substr(0, colon);
    string newWorkflow = process.substr(colon + 1, process.length() - colon - 1);
    Cmp c(exp);
    return {c, newWorkflow};
}

bool search(const vector<int>& v, unordered_map<string, vector<pair<Cmp, string>>>& mp, 
            string workflow){
    if (workflow == "A"){
        return true;
    }
    if (workflow == "R"){
        return false;
    }
    const vector<pair<Cmp, string>>& processes = mp[workflow];
    for (const pair<Cmp, string>& p : processes){
        Cmp c = p.first;
        if (c(v)){
            return search(v, mp, p.second);
        }
    }
    return false;
}

ll searchTwo(const vector<pair<ll, ll>>& v, const string& workflow, unordered_map<string, 
            vector<pair<Cmp, string>>>& mp){
    if (workflow == "A"){
        ll ans = 1;
        for (int i = 0; i < v.size(); ++i){
            ans *= (v[i].second - v[i].first + 1);
        }
        return ans;
    }
    if (workflow == "R"){
        return 0;
    }
    vector<pair<ll, ll>> curr = v;
    const vector<pair<Cmp, string>>& processes = mp[workflow];
    ll tot = 0;
    for (pair<Cmp, string> process : processes){
        Cmp c = process.first;
        //last process
        if (c.getThreshold() == INT_MIN){
            tot += searchTwo(curr, process.second, mp);
            break;
        }
        int index = c.getIndex();
        vector<int> temp = {0, 0, 0, 0};
        vector<int> temp2 = temp;
        temp[index] = curr[index].first;
        temp[index] = curr[index].second;
        //entire interval doesn't satisfy
        if (!c(temp) && !c(temp2)){
            continue;
        }
        //entire interval satisfies the property
        if (c(temp) && c(temp2)){
            tot += searchTwo(curr, process.second, mp);
            break;
        }
        //some overlap (separate into two)
        //send threshold + 1 to the recursion
        if (c.getGT()){
            vector<pair<ll, ll>> copy = curr;
            copy[index].first = c.getThreshold() + 1;
            curr[index].second = c.getThreshold();
            tot += searchTwo(copy, process.second, mp);
        }
        else{
            vector<pair<ll, ll>> copy = curr;
            copy[index].second = c.getThreshold() - 1;
            curr[index].first = c.getThreshold();
            tot += searchTwo(copy, process.second, mp);
        }
    }
    return tot;
}

ll partTwo(){
    // ifstream fin("day19sample.txt");
    ifstream fin("day19input.txt");
    unordered_map<string, vector<pair<Cmp, string>>> mp;
    string line;
    getline(fin, line);
    while (line != ""){
        int bracket = indexOf(line, '{');
        string workflow = line.substr(0, bracket);
        string processes = line.substr(bracket + 1, line.length() - bracket - 2);
        vector<pair<Cmp, string>> v;
        istringstream iss(processes);
        string process;
        while (getline(iss, process, ',')){
            pair<Cmp, string> p = createProcess(process);
            v.push_back(p);
        }
        mp[workflow] = v;
        getline(fin, line);
    }
    vector<pair<ll, ll>> v = {{1, 4000}, {1, 4000}, {1, 4000}, {1, 4000}};
    return searchTwo(v, "in", mp);
}

ll partOne(){
    // ifstream fin("day19sample.txt");
    ifstream fin("day19input.txt");
    unordered_map<string, vector<pair<Cmp, string>>> mp;
    string line;
    getline(fin, line);
    while (line != ""){
        int bracket = indexOf(line, '{');
        string workflow = line.substr(0, bracket);
        string processes = line.substr(bracket + 1, line.length() - bracket - 2);
        vector<pair<Cmp, string>> v;
        istringstream iss(processes);
        string process;
        while (getline(iss, process, ',')){
            pair<Cmp, string> p = createProcess(process);
            v.push_back(p);
        }
        mp[workflow] = v;
        getline(fin, line);
    }
    ll ans = 0;
    while (getline(fin, line)){
        line = line.substr(1, line.length() - 2);
        istringstream iss(line);
        string rating;
        vector<int> v;
        while (getline(iss, rating, ',')){
            v.push_back(stoi(rating.substr(2, rating.length() - 2)));
        }
        if (search(v, mp, "in")){
            ans += v[0] + v[1] + v[2] + v[3];
        }
    }
    return ans;
}

int main(){
    ll p1 = partOne();
    ll p2 = partTwo();
    cout << "Part one: " << p1 << endl;
    cout << "Part two: " << p2 << endl;
}