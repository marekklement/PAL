#include <iostream>
#include <string>
#include <queue>
#include <map>

using namespace std;

inline void readNumber(int *x) {
    register char c = getchar_unlocked();
    *x = 0;
    for (; (c < 48) || (c > 57); c = getchar_unlocked());
    for (; (c > 47) && (c < 58); c = getchar_unlocked()) {
        *x = (int) ((((*x) << 1) + ((*x) << 3)) + c - 48);
    }
}

void getChar(string &str)
{
    char c = '0';
    while((c = getchar_unlocked()) && (c != -1 && c != '\n' && c != '\r'))
    {
        str += c;
    }
}

int nodesMin;
int nodeMax;
int depthMin;
int depthMax;

string t1;
string t2;

char nula = '0';

map<string,int> compsT1;

void read() {
    readNumber(& nodesMin);
    readNumber(& nodeMax);
    readNumber(& depthMin);
    readNumber(& depthMax);

    getChar(t1);
    getChar(t2);
}

void print(queue<char> qu){
    string s = "";
    while(!qu.empty()){
        s += qu.front();
        qu.pop();
    }
    cout << s << endl;
}

void solve(string str, int depthLocalMax){
    queue<char> qu;
    vector<int> depths(depthLocalMax + 2);
    fill(depths.begin(), depths.end(), 0);
    int nodeCount = 0;
    int depthCount = 0;
    int maximumD = 0;
    bool flag = false;
    for(char& c : str) {
        //print(qu);
        if(c == nula){
            if(qu.empty()){
               nodeCount = 0;
               depthCount = -1;
               maximumD = 0;
               fill(depths.begin(), depths.end(), 0);
            }
            qu.push(c);
            depthCount++;
            nodeCount++;
            depths.at(depthCount)++;
            if(!flag) {
                if (nodeCount > nodeMax || depthCount > depthLocalMax) {
                    if(depthCount -1 < depthMin){
                        while (!qu.empty()) {
                            qu.pop();
                        }
                        continue;
                    }
                    qu.pop();
                    depthCount--;
                    nodeCount--;
                    maximumD--;
                    if (depths.at(1) == 1) {
                        for (int i = 0; i <= depthCount; ++i) {
                            depths.at(i) = depths.at(i + 1);
                        }
                        for (int i = depthCount + 1; i < depths.size(); ++i) {
                            depths.at(i) = 0;
                        }
                        //depths.at(depthCount) = 0;
                    } else {
                        flag = true;
                    }
                }
            }
            maximumD = max(maximumD, depthCount);
        } else {
            if(qu.empty()) continue;
            qu.push(c);
            depthCount--;
            if (depthCount == -1){
                if(!flag) {
                    if (maximumD >= depthMin && nodeCount >= nodesMin) {
                        string comp = "";
                        while (!qu.empty()) {
                            comp += qu.front();
                            qu.pop();
                        }
                        if (compsT1.find(comp) == compsT1.end()) {
                            //cout << " FINAL " << endl;
                            //cout << comp << endl;
                            //cout << " ENDL " << endl;
                            compsT1[comp] = 1;
                            if(maximumD -1 >= depthMin) {
                                solve(comp, depthLocalMax - 1);
                            }
                        }
                    } else {
                        while (!qu.empty()) {
                            qu.pop();
                        }
                    }
                } else {
                    string comp = "";
                    while (!qu.empty()) {
                        comp += qu.front();
                        qu.pop();
                    }
                    flag = false;
                    solve(comp, depthLocalMax);
                }
            }
        }
    }
}

int compare(){
    int count = 0;
    map<string, int>::iterator it;

    for ( it = compsT1.begin(); it != compsT1.end(); it++ )
    {
        string::size_type nPos = 0;
        //cout << it->first << endl;
        while ((nPos = t2.find(it->first, nPos)) != string::npos){
            count++;
            nPos += it->first.size();

        }
    }
    return count;
}

int main() {
    read();
    solve(t1, depthMax);
    cout << compare() << endl;
    return 0;
}
