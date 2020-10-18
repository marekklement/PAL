#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct Way {
    int from;
    vector<int> to;
    vector<int> froms;
} ;

inline void readNumber(int *x) {
    register char c = getchar_unlocked();
    *x = 0;
    for (; (c < 48) || (c > 57); c = getchar_unlocked());
    for (; (c > 47) && (c < 58); c = getchar_unlocked()) {
        *x = (int) ((((*x) << 1) + ((*x) << 3)) + c - 48);
    }
}

int busStops;
int busConnections;
vector<Way> cityMap;

void read(){
    readNumber(& busStops);
    readNumber(& busConnections);
    int from, to;
    for(int i = 0; i < busStops; i++){
        Way wayNodeLess = {.from = i};
        cityMap.push_back(wayNodeLess);
    }
    for(int i = 0; i < busConnections; i++) {
        readNumber(&from);
        readNumber(&to);
        Way way = cityMap.at(from);
        vector<int> toes = way.to;
        toes.push_back(to);
        way = {.from = way.from, .to = toes, .froms = way.froms};
        cityMap.at(from) = way;
        // handle to
        Way wayTo = cityMap.at(to);
        vector<int> froms = wayTo.froms;
        froms.push_back(from);
        wayTo = {.from = wayTo.from, .to = wayTo.to, .froms = froms};
        cityMap.at(to) = wayTo;
    }
}


stack<int> stck;
int* diskStash;
int* low;
int* strongComponents;
bool* stacked;
bool* saves;
int counter;
int current;

void init(){
    diskStash = new int[busStops];
    low = new int[busStops];
    strongComponents = new int[busStops];
    stacked = new bool[busStops];
    saves = new bool[busStops];
    for(int i = 0; i < busStops; i++){
        diskStash[i] = -1;
        stacked[i] = false;
        saves[i] = true;
        strongComponents[i] = -1;
    }
}

void tarjan(int number){
    diskStash[number] = low[number] = counter++;
    stck.push(number);
    stacked[number] = true;
    const vector<int> &out = cityMap.at(number).to;
    int num = out.size();
    for (int i=0; i < num; ++i){
        const int &node = out[i];
        if (diskStash[node] == -1){
            tarjan(node);
            low[number] = min(low[number], low[node]);
        }else if (stacked[node]){
            low[number] = min(low[number], low[node]);
        }
    }
    if (diskStash[number] == low[number]){
        int node;
        while(1){
            node = stck.top();
            stck.pop();
            stacked[node] = false;
            strongComponents[node] = current;
            if(number == node) break;
        }
        current++;
    }
}

int* kondenzat;
vector<Way> kondenzGraph;

void findSaves(){
    for(int i = 0; i < busStops; i++){
        if(!saves[i]) continue;
        Way way = cityMap.at(i);
        vector<int> froms = way.froms;
        int size = froms.size();
        for(int j = 0; j < size; j++){
            if(strongComponents[i] != strongComponents[froms.at(j)]){
                saves[i] = false;
                break;
            }
        }
        if(!saves[i]) continue;
        vector<int> toes = way.to;
        int num = toes.size();
        for(int j = 0; j < num; j++){
            if(strongComponents[i] != strongComponents[toes.at(j)]){
                saves[i] = false;
                break;
            }
        }
    }
}

void makeKondenzedGraph(){
    for(int i = 0; i < current; i++){
        Way way = {.from = i};
        kondenzGraph.push_back(way);
    }
    bool** added = new bool*[current];
    for(int i = 0; i < current; i++){
        added[i] = new bool[current];
        for (int j = 0; j < current; ++j) {
            added[i][j] = false;
        }
    }
    for(int i = 0; i < busStops; i++){
        if(saves[i]) continue;
        vector<int> toes = cityMap.at(i).to;
        int end = toes.size();
        for(int j = 0; j < end; j++){
            int tod = toes.at(j);
            if(strongComponents[i] != strongComponents[tod] && !added[strongComponents[i]][strongComponents[tod]]){
                added[strongComponents[i]][strongComponents[tod]] = true;
                Way way = kondenzGraph.at(strongComponents[i]);
                vector<int> vec = way.to;
                vec.push_back(strongComponents[tod]);
                way.to = vec;
                kondenzGraph.at(strongComponents[i]) = way;
            }
        }
    }
}

int* visitedValues;

int dfs(int sum, int u){
    int ret = sum + kondenzat[u];
    int currentMax = 0;
    if(visitedValues[u] == -1) {
        vector<int> toes = kondenzGraph.at(u).to;
        int num = toes.size();
        for (int i = 0; i < num; i++) {
            int v = toes.at(i);
            int back = dfs(0, v);
            if (back > currentMax) currentMax = back;
        }
        visitedValues[u] = currentMax;
    } else {
        currentMax = visitedValues[u];
    }
    return ret + currentMax;
}

int kondenz(){
    kondenzat = new int[current];
    visitedValues = new int[current];
    for(int i = 0; i < current; i++){
        kondenzat[i] = 0;
        visitedValues[i] = -1;
    }
    for(int i = 0; i < busStops; i++){
        if(saves[i]){
            kondenzat[strongComponents[i]] += 1;
        }
    }
    int top = 0;

    for(int i = 0; i < current; i++){
        int number = dfs(0,i);
        if(number > top){
            top = number;
        }
    }
    return top;
}

void remove(){
    delete[] diskStash;
    delete[] low;
    delete[] strongComponents;
    delete[] stacked;
    delete[] saves;
    delete[] visitedValues;
    delete[] kondenzat;
}

int main() {
    read();
    init();
    for (int i = 0; i < busStops; i++) {
        if(diskStash[i] == -1)
            tarjan(i);
    }
    findSaves();
    makeKondenzedGraph();
    int end = kondenz();
    remove();
    printf("%d",end);
    return 0;
}
