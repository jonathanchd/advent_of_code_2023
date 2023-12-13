#include "../imports.hpp"
using namespace std;

#define ll long long

ll testVertical(const vector<string>& v);
ll testHorizontal(const vector<string>& v);
void printVector(const vector<string>& v);

//return -1 if no vertical line
vector<ll> testVerticalPt2(const vector<string>& v){
    const int n = v.size();
    const int m = v[0].size();
    //i == number of columns to the left
    vector<ll> stuff;
    for (int i = 1; i < m; ++i){
        bool works = true;
        //line is between i - 1 and i
        for (int row = 0; row < n; ++row){
            if (!works){
                break;
            }
            for (int col = max(0, 2 * i - m); col < i; ++col){
                int reflection = 2 * i - col - 1;
                if (v[row][col] != v[row][reflection]){
                    works = false;
                    break;
                }
            }
        }
        if (works){
            stuff.push_back(i);
        }
    }
    return stuff;
}

//return -1 if no horizontal line
vector<ll> testHorizontalPt2(const vector<string>& v){
    vector<string> rotated(v[0].size(), string(v.size(), 'a'));
    int rows = v.size();
    int cols = v[0].size();
    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < cols; ++j){
            rotated[cols - j - 1][i] = v[i][j];
        }
    }
    return testVerticalPt2(rotated);
}



ll dayTwoHelper(vector<string>& v){
    map<char, char> mp = {{'.', '#'}, {'#', '.'}};
    const int n = v.size();
    const int m = v[0].size();
    ll original = testVertical(v);
    if (original == -1){
        original = 100 * testHorizontal(v);
    }
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            v[i][j] = mp[v[i][j]];
            vector<ll> vertical = testVerticalPt2(v);
            if (vertical.size() != 0 ){
                for (ll val : vertical){
                    if (val != original){
                        return val;
                    }
                }
            }
            vector<ll> horizontal = testHorizontalPt2(v);
            if (horizontal.size() != 0){
                for (int val : horizontal){
                    if (val * 100 != original){
                        return val * 100;
                    }
                }
            }
            v[i][j] = mp[v[i][j]];
        }
    }
    return -1;
}

ll partTwo(){
    ifstream fin("day13input.txt");
    // ifstream fin("day13sample.txt");
    // ifstream fin("test.txt");
    string s;
    ll ans = 0;
    int cse = 0;
    while (getline(fin, s)){
        vector<string> v;
        while (s != ""){
            v.push_back(s);
            getline(fin, s);
        }
        // cout << "Case: " << cse << endl;
        ++cse;
        ans += dayTwoHelper(v);
        
    }
    return ans;
}

//return -1 if no horizontal line
ll testHorizontal(const vector<string>& v){
    vector<string> rotated(v[0].size(), string(v.size(), 'a'));
    int rows = v.size();
    int cols = v[0].size();
    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < cols; ++j){
            rotated[cols - j - 1][i] = v[i][j];
        }
    }
    return testVertical(rotated);
}

//return -1 if no vertical line
ll testVertical(const vector<string>& v){
    const int n = v.size();
    const int m = v[0].size();
    //i == number of columns to the left
    for (int i = 1; i < m; ++i){
        bool works = true;
        //line is between i - 1 and i
        for (int row = 0; row < n; ++row){
            if (!works){
                break;
            }
            for (int col = max(0, 2 * i - m); col < i; ++col){
                int reflection = 2 * i - col - 1;
                if (v[row][col] != v[row][reflection]){
                    works = false;
                    break;
                }
            }
        }
        if (works){
            return i;
        }
    }
    return -1;
}

void printVector(const vector<string>& v){
    for (const string& s : v){
        cout << s << endl;
    }
}

ll dayOneHelper(const vector<string>& v){
    ll vertical = testVertical(v);
    if (vertical != -1){
        // printVector(v);
        // cout << "vert " << vertical << endl << endl;
        return vertical;
    }
    // printVector(v);
    // int horizontal = testHorizontal(v);
    // cout << "hori " << horizontal << endl << endl;
    return testHorizontal(v) * 100;
}

ll partOne(){
    ifstream fin("day13input.txt");
    // ifstream fin("day13sample.txt");
    string s;
    ll ans = 0;
    int cse = 0;
    while (getline(fin, s)){
        vector<string> v;
        while (s != ""){
            v.push_back(s);
            getline(fin, s);
        }
        // cout << "Case: " << cse << endl;
        ans += dayOneHelper(v);
        ++cse;
    }
    return ans;
}

int main(){
    ll p1 = partOne();
    ll p2 = partTwo();
    cout << "Part one: " << p1 << endl;
    cout << "Part two: " << p2 << endl;
}