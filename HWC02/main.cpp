#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <iterator>

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
int* d;
int* low;
int* scc;
bool* stacked;
bool* saves;
int counter;
int current;

void init(){
    d = new int[busStops];
    low = new int[busStops];
    scc = new int[busStops];
    stacked = new bool[busStops];
    saves = new bool[busStops];
    for(int i = 0; i < busStops; i++){
        d[i] = -1;
        stacked[i] = false;
        saves[i] = true;
    }
}

void tarjan(int u){
    d[u] = low[u] = counter++;
    stck.push(u);
    stacked[u] = true;
    const vector<int> &out = cityMap.at(u).to;
    for (int k=0, m=out.size(); k<m; ++k){
        const int &v = out[k];
        if (d[v] == -1){
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }else if (stacked[v]){
            low[u] = min(low[u], low[v]);
        }
    }
    if (d[u] == low[u]){
        int v;
        do{
            v = stck.top();
            stck.pop();
            stacked[v] = false;
            scc[v] = current;
        }while (u != v);
        current++;
    }
}

int* kondenzat;
vector<Way> kondenzGraph;

void printSCC(){
    for(int i = 0; i < current; i++) {
        printf("Node %d have number of saves: %d with nexts", i, kondenzat[i]);
        for (int j = 0; j < kondenzGraph.at(i).to.size(); j++) {
            printf(" %d", kondenzGraph.at(i).to.at(j));
        }
        printf("\n");
    }
}

void findSaves(){
    for(int i = 0; i < busStops; i++){
        if(!saves[i]) continue;
        Way way = cityMap.at(i);
        vector<int> froms = way.froms;
        int size = froms.size();
        for(int j = 0; j < size; j++){
            if(scc[i] != scc[froms.at(j)]){
                saves[i] = false;
                break;
            }
        }
        if(!saves[i]) continue;
        vector<int> toes = way.to;
        int num = toes.size();
        for(int j = 0; j < num; j++){
            if(scc[i] != scc[toes.at(j)]){
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
    bool added[current][current];
    for(int i = 0; i < current; i++){
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
            if(scc[i] != scc[tod] && !added[scc[i]][scc[tod]]){
                added[scc[i]][scc[tod]] = true;
                kondenzGraph.at(scc[i]).to.push_back(scc[tod]);
            }
        }
    }
}

int dfs(int sum, int u){
    vector<int> toes = kondenzGraph.at(u).to;
    int num = toes.size();
    int ret = sum + kondenzat[u];
    int currentMax = 0;
    for (int i=0; i < num; i++){
        int v = toes.at(i);
        int back = dfs(0,v);
        if(back > currentMax) currentMax = back;
    }
    return ret + currentMax;
}

int kondenz(){
    kondenzat = new int[current];
    bool visited[current];
    for(int i = 0; i < current; i++){
        kondenzat[i] = 0;
        visited[i] = false;
    }
    for(int i = 0; i < busStops; i++){
        if(saves[i]){
            kondenzat[scc[i]] += 1;
        }
    }
    printSCC();
    printf("\n");
    //
    int top = 0;

    for(int i = 0; i < current; i++){
        int number = dfs(0,i);
        if(number > top){
            top = number;
        }
    }
    return top;
}

int main() {
    read();
    init();
    tarjan(0);
    findSaves();
    makeKondenzedGraph();
    int end = kondenz();
    //printSCC();
    printf("%d",end);
    return 0;
}
