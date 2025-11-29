#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <fstream>
#include <cmath>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

// Linear Regression (simple)
double predict_demand(double x, double m, double b){
    return m * x + b;
}

// Fenwick Tree (BIT)
struct BIT {
    int n;
    vector<double> tree;
    BIT(int n): n(n), tree(n+1,0) {}
    void update(int i, double val){
        while(i <= n){
            tree[i] += val;
            i += i & -i;
        }
    }
    double query(int i){
        double s = 0;
        while(i > 0){
            s += tree[i];
            i -= i & -i;
        }
        return s;
    }
};

// Dijkstra’s
vector<double> dijkstra(int n, vector<vector<pair<int,double>>>& adj, int src){
    vector<double> dist(n, 1e18);
    priority_queue<pair<double,int>, vector<pair<double,int>>, greater<pair<double,int>>> pq;

    dist[src]=0;
    pq.push({0,src});

    while(!pq.empty()){
        auto [d,u] = pq.top(); pq.pop();
        if(d != dist[u]) continue;

        for(auto &e: adj[u]){
            int v = e.first;
            double w = e.second;
            if(dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int main(){
    ifstream f("solar_data.json");
    json data;
    f >> data;

    cout << "Micro Solar Energy Trading Platform Loaded\n";

    double slope = data["regression"]["slope"];
    double intercept = data["regression"]["intercept"];

    double x = data["predict_hour"];
    cout << "Predicted energy demand at hour " << x << ": "
         << predict_demand(x, slope, intercept) << "\n";

    int n = data["grid_nodes"];
    vector<vector<pair<int,double>>> adj(n);

    for(auto &e : data["edges"]){
        int u = e["u"], v = e["v"];
        double w = e["w"];
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    auto dist = dijkstra(n, adj, 0);
    cout << "Energy flow cost from node 0 to last node: " 
         << dist[n-1] << "\n";

    BIT bit(10);
    for(int i=1;i<=10;i++){
        bit.update(i, i*2);
    }

    cout << "Total energy used in first 5 houses: " 
         << bit.query(5) << "\n";

    return 0;
}
