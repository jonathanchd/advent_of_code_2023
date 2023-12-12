#include "../imports.hpp"
using namespace std;

#define ll long long

map<tuple<int, int, int>, ll> dp;
ll day2search(const string& line, vector<int>& nums, int index, int currBlock, int currLength){
    tuple<int, int, int> key(index, currBlock, currLength);
    if (dp.find(key) != dp.end()){
        return dp[key];
    }
    if (index == line.length()){
        if (currBlock == nums.size() && currLength == 0){
            return 1;
        }
        if (currBlock == nums.size() - 1 && currLength == nums[currBlock]){
            return 1;
        }
        return 0;
    }
    ll ans = 0;
    if (line[index] == '?'){
        if (currLength == 0){
            ans += day2search(line, nums, index + 1, currBlock, 0);
        }
        else if (currLength > 0 && currBlock < nums.size() && nums[currBlock] == currLength){
            ans += day2search(line, nums, index + 1, currBlock + 1, 0);
        }
        ans += day2search(line, nums, index + 1, currBlock, currLength + 1);
    }
    else if (line[index] == '.'){
        if (currLength == 0){
            ans += day2search(line, nums, index + 1, currBlock, 0);
        }
        else if (currLength > 0 && currBlock < nums.size() && nums[currBlock] == currLength){
            ans += day2search(line, nums, index + 1, currBlock + 1, 0);
        }
    }
    else if (line[index] == '#'){
        ans += day2search(line, nums, index + 1, currBlock, currLength + 1);
    }
    dp[key] = ans;
    return dp[key];
}

ll dayTwoHelper(string line, string numbers){
    vector<int> nums;
    istringstream iss(numbers);
    string s;
    while (getline(iss, s, ',')){
        nums.push_back(stoi(s));
    }
    line = line + "?" + line + "?" + line + "?" + line + "?" + line;
    vector<int> dup;
    for (int i = 0; i < 5; ++i){
        dup.insert(dup.end(), nums.begin(), nums.end());
    }
    return day2search(line, dup, 0, 0, 0);
}

ll partTwo(){
    ifstream fin("day12input.txt");
    // ifstream fin("day12sample.txt");
    string line, numbers;
    ll ans = 0;
    while (fin >> line >> numbers){
        dp.clear();
        ans += dayTwoHelper(line, numbers);
    }
    return ans;
}

vector<int> breakIntoSeparate(string line){
    line += ".";
    string curr = "";
    vector<int> ret;
    for (int i = 0; i < line.size(); ++i){
        if (line[i] == '#'){
            curr += line[i];
        }
        else{
            if (curr != ""){
                ret.push_back(curr.size());
            }
            curr = "";
        }
    }
    return ret;
}

bool containsQues(const string& line, int index){
    for (int i = index + 1; i < line.size(); ++i){
        if (line[i] == '?'){
            return true;
        }
    }
    return false;
}

bool valid(const string& line, vector<int>& nums){
    vector<int> counts = breakIntoSeparate(line);
    if (counts.size() != nums.size()){
        return false;
    }
    for (int i = 0; i < nums.size(); ++i){
        if (nums[i] != counts[i]){
            return false;
        }
    }
    return true;
}

void search(string line, vector<int>& nums, int index, ll& ans, const int& limit, int poundCount){
    if (!containsQues(line, index)){
        if (valid(line, nums)){
            ++ans;
        }
        return;
    }
    if (poundCount > limit){
        return;
    }
    
    for (int i = index; i < line.size(); ++i){
        if (line[i] == '?'){
            //try as # or .
            string poundKey = line;
            poundKey[i] = '#';
            search(poundKey, nums, i, ans, limit, poundCount + 1);
            string period = line;
            period[i] = '.';
            search(period, nums, i, ans, limit, poundCount);
            return;
        }
    }
}

ll dayOneHelper(string line, string numbers){
    vector<int> nums;
    istringstream iss(numbers);
    string s;
    while (getline(iss, s, ',')){
        nums.push_back(stoi(s));
    }
    int limit = 0;
    for (int val : nums){
        limit += val;
    }
    int poundCount = 0;
    for (char c : line){
        poundCount += c == '#';
    }
    ll ans = 0;
    search(line, nums, 0, ans, limit, poundCount);
    return ans;
}

ll partOne(){
    ifstream fin("day12input.txt");
    // ifstream fin("day12sample.txt");
    string line, numbers;
    ll ans = 0;
    while (fin >> line >> numbers){
        ans += dayOneHelper(line, numbers);
    }
    return ans;
}

int main(){
    ll p1 = partOne();
    ll p2 = partTwo();
    cout << "Part one: " << p1 << endl;
    cout << "Part two: " << p2 << endl;
}