#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

struct Point {
    double x, y;
};

double euclidean(Point a, Point b){
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

int findNearestAuto(vector<Point>& autos, Point passenger){
    double bestDist = 1e9;
    int bestIndex = -1;

    for(int i=0; i<(int)autos.size(); i++){
        double d = euclidean(autos[i], passenger);
        if(d < bestDist){
            bestDist = d;
            bestIndex = i;
        }
    }
    return bestIndex;
}

// Simple Dijkstra for route cost
vector<int> dijkstra(int n, vector<vector<pair<int,int>>>& adj, int src){
    vector<int> dist(n, 1e9);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    dist[src]=0;
    pq.push({0,src});

    while(!pq.empty()){
        auto [d,u] = pq.top(); pq.pop();
        if(d!=dist[u]) continue;

        for(auto& e: adj[u]){
            int v=e.first, w=e.second;
            if(dist[u]+w < dist[v]){
                dist[v] = dist[u]+w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int main(){
    ifstream f("transport_data.json");
    json data; 
    f >> data;

    cout << "Shared Auto Transport Optimization Platform Loaded\n";

    vector<Point> autos;
    for(auto& a : data["autos"])
        autos.push_back({a["x"], a["y"]});

    vector<Point> passengers;
    for(auto& p : data["passengers"])
        passengers.push_back({p["x"], p["y"]});

    for(int i=0;i<passengers.size();i++){
        int nearest = findNearestAuto(autos, passengers[i]);
        cout << "Passenger " << i << " nearest auto index: " << nearest << endl;
    }

    int n = data["graph_nodes"];
    vector<vector<pair<int,int>>> adj(n);
    for(auto& e : data["edges"]){
        int u=e["u"], v=e["v"], w=e["w"];
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    auto dist = dijkstra(n, adj, 0);
    cout << "Distance from node 0 to last node: " << dist[n-1] << endl;

    return 0;
}

