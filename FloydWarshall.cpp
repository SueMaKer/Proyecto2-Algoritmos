#include "FloydWarshall.hpp"
#include <iostream>
#include <limits>

FloydWarshall::FloydWarshall(int vertices) : cantNodes(vertices) {
    dist.assign(cantNodes, vector<int>(cantNodes, Config::INF));
    next.assign(cantNodes, vector<int>(cantNodes, -1));
    for (int i = 0; i < cantNodes; ++i) {
        dist[i][i] = 0;
    }
}

void FloydWarshall::addEdge(int node1, int node2, int cost) {
    dist[node1][node2] = cost;
    next[node1][node2] = node2;
}

//Poco eficiente O(n^3)
void FloydWarshall::run() {
    for (int k = 0; k < cantNodes; ++k){
        for (int i = 0; i < cantNodes; ++i){
            for (int j = 0; j < cantNodes; ++j){
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}

int FloydWarshall::getDistance(int node1, int node2) const {
    return dist[node1][node2];
}

vector<int> FloydWarshall::getPath(int node1, int node2) const {
    if (next[node1][node2] == -1) return {};
    vector<int> path = { node1 };
    while (node1 != node2) {
        node1 = next[node1][node2];
        path.push_back(node1);
    }
    return path;
}

void FloydWarshall::printDistanceMatrix() const {
    for (int i = 0; i < cantNodes; ++i) {
        for (int j = 0; j < cantNodes; ++j) {
            if (dist[i][j] >= Config::INF)
                cout << "INF ";
            else
                cout << dist[i][j] << " ";
        }
        cout << '\n';
    }
}
