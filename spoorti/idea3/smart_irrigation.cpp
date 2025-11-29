
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <climits>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;

// Global containers (filled dynamically from JSON)
vector<int> moistureLevels;
vector<vector<pair<int,int>>> irrigationGraph;

// Load JSON at runtime
void loadJSON(string filename) {
    ifstream f(filename);
    json data;
    f >> data;

    moistureLevels.clear();
    for (auto &z : data["farm_zones"]) {
        moistureLevels.push_back(z["moisture"]);
    }

    int maxNode = 0;
    for (auto &e : data["irrigation_channels"]) {
        maxNode = max(maxNode, max((int)e["from"], (int)e["to"]));
    }
    irrigationGraph.assign(maxNode + 1, {});

    for (auto &e : data["irrigation_channels"]) {
        int u = e["from"];
        int v = e["to"];
        int c = e["cost"];
        irrigationGraph[u].push_back({v, c});
        irrigationGraph[v].push_back({u, c});
    }
}

vector<int> dijkstra(int V, vector<vector<pair<int,int>>> &g, int src) {
    vector<int> dist(V, INT_MAX);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    dist[src] = 0;
    pq.push({0, src});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        for (auto &edge : g[u]) {
            int v = edge.first;
            int w = edge.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int greedyWaterDistribution(vector<int> &moist) {
    int idx = 0, mn = moist[0];
    for (int i = 1; i < moist.size(); i++)
        if (moist[i] < mn) mn = moist[i], idx = i;
    return idx;
}

int main() {
    string filename;
    cout << "Enter JSON file name: ";
    cin >> filename;

    loadJSON(filename);

    cout << "Loaded " << moistureLevels.size() << " farm zones.\n";

    int needyField = greedyWaterDistribution(moistureLevels);
    cout << "Field needing most water: " << needyField << endl;

    int V = irrigationGraph.size();
    auto dist = dijkstra(V, irrigationGraph, 0);
    cout << "Shortest water route to last field: " << dist[V-1] << endl;

    return 0;
}
