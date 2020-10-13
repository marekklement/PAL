#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
    int weight;
    int index;
    int level;
} ;

struct NodeGreater {
    bool operator()(const Node &a, const Node &b) const {
        return a.weight > b.weight;
    }
};

int capitalCity;
int cities;
int roads;
vector<vector<Node>> tableOfRoads;

void read() {
    cin >> cities;
    cin >> roads;
    cin >> capitalCity;

    vector<vector<Node>> map(cities);
    for(int i = 0; i < roads; i++){
        int from, to, cost;
        cin >> from;
        cin >> to;
        cin >> cost;
        Node first = {.index = from, .weight = cost};
        Node second = {.index = to, .weight = cost};
        map.at(from).push_back(second);
        map.at(to).push_back(first);
    }
    tableOfRoads = map;
}

void getLevels(){
    int levels[cities];
    queue<Node> front;
    bool visited[cities];
    visited[capitalCity] = true;
    int visitedAll = 1;

    int num = tableOfRoads.at(capitalCity).size();
    for (int i = 0; i < num; i++) {
        tableOfRoads.at(capitalCity).at(i).level = 1;
        levels[tableOfRoads.at(capitalCity).at(i).index] = 1;
        front.push(tableOfRoads.at(capitalCity).at(i));
    }
    while (!front.empty()) {
        if(visitedAll == cities) break;
        Node current = front.front();
        front.pop();
        if (visited[current.index]) {
            continue;
        }
        int level = current.level + 1;
        visited[current.index] = true;
        visitedAll+=1;
        int number = tableOfRoads.at(current.index).size();
        for (int i = 0; i < number; i++) {
            Node node = tableOfRoads.at(current.index).at(i);
            if(levels[node.index] != 0){
                tableOfRoads.at(current.index).at(i).level = levels[node.index];
            } else if (node.index == capitalCity) {
                tableOfRoads.at(current.index).at(i).level = 0;
            } else {
                tableOfRoads.at(current.index).at(i).level = level;
                levels[tableOfRoads.at(current.index).at(i).index] = level;
                front.push(tableOfRoads.at(current.index).at(i));
            }

        }
    }
}

int prim() {
    int cost = 0;
    getLevels();
    int numberOfCities = tableOfRoads.size();

    priority_queue<Node, vector<Node>, NodeGreater> primaryQueue;
    priority_queue<Node, vector<Node>, NodeGreater> secondPriority;

    bool visited[numberOfCities];

    visited[capitalCity] = true;
    int visitedAll = 1;

    int num = tableOfRoads.at(capitalCity).size();
    for (int i = 0; i < num; i++) {
        Node node = tableOfRoads.at(capitalCity).at(i);
        primaryQueue.push(node);
    }
    while (!primaryQueue.empty() || !secondPriority.empty()) {
        if(visitedAll == numberOfCities){
            break;
        }
        if(primaryQueue.empty()){
            priority_queue<Node, vector<Node>, NodeGreater> swap = primaryQueue;
            primaryQueue = secondPriority;
            secondPriority = swap;
        }
        Node current = primaryQueue.top();
        primaryQueue.pop();

        if (visited[current.index]) {
            continue;
        }
        visited[current.index] = true;
        visitedAll+=1;
        cost += current.weight;
        if(visitedAll == numberOfCities) break;
        vector<Node> vector = tableOfRoads.at(current.index);
        int number = vector.size();
        for (int i = 0; i < number; i++) {
            Node node = vector.at(i);
            if(visited[node.index]) continue;
            if(node.level == current.level ) {
                primaryQueue.push(node);
            } else {
                secondPriority.push(node);
            }
        }
    }

    return cost;
}

int main() {
    read();
    printf("%d", prim());
}
