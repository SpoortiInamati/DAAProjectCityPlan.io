
#include <bits/stdc++.h>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;

// --- GeoHash (simplified) ---
string geoHash(double lat, double lon) {
    return to_string((int)lat) + "_" + to_string((int)lon);
}

// --- QuadTree Node ---
struct QuadNode {
    double x, y;
    string region;
    QuadNode* nw; QuadNode* ne; QuadNode* sw; QuadNode* se;
    QuadNode(double _x,double _y,string r):x(_x),y(_y),region(r),nw(NULL),ne(NULL),sw(NULL),se(NULL){}
};

// Insert into quadtree
void insertQuad(QuadNode*& root, double x, double y, string r) {
    if(!root) { root = new QuadNode(x,y,r); return; }
    if(x < root->x && y < root->y) insertQuad(root->sw, x,y,r);
    else if(x < root->x && y >= root->y) insertQuad(root->nw, x,y,r);
    else if(x >= root->x && y < root->y) insertQuad(root->se, x,y,r);
    else insertQuad(root->ne, x,y,r);
}

// --- Graph for Dijkstra ---
struct Edge { int to; double w; };
vector<vector<Edge>> graph;

vector<double> dijkstra(int start) {
    int n = graph.size();
    vector<double> dist(n, 1e18);
    priority_queue<pair<double,int>, vector<pair<double,int>>, greater<pair<double,int>>> pq;
    dist[start] = 0;
    pq.push({0,start});

    while(!pq.empty()) {
        auto [d,u] = pq.top(); pq.pop();
        if(d!=dist[u]) continue;
        for(auto &e : graph[u]) {
            if(dist[e.to] > d + e.w) {
                dist[e.to] = d + e.w;
                pq.push({dist[e.to], e.to});
            }
        }
    }
    return dist;
}

// --- KMP Pattern Search ---
vector<int> buildKMP(string p) {
    int n=p.size(), j=0;
    vector<int> lps(n,0);
    for(int i=1;i<n;i++){
        while(j>0 && p[i]!=p[j]) j=lps[j-1];
        if(p[i]==p[j]) j++;
        lps[i]=j;
    }
    return lps;
}
bool kmpSearch(string t, string p) {
    auto lps = buildKMP(p);
    int i=0,j=0;
    while(i < (int)t.size()) {
        if(t[i]==p[j]) i++, j++;
        else if(j>0) j=lps[j-1];
        else i++;
        if(j == (int)p.size()) return true;
    }
    return false;
}

// --- Greedy time slot assignment ---
string assignTimeSlot(double crowd) {
    if(crowd < 0.3) return "Morning";
    if(crowd < 0.6) return "Afternoon";
    return "Evening";
}

// --- Main JSON-driven app ---
int main() {
    ifstream f("eco_data.json");
    if(!f.is_open()) { cout << "JSON file missing!\n"; return 0; }

    json data; 
    f >> data;

    cout << "Eco‑Tourism Route Optimization System\n";

    // Load POIs
    vector<pair<double,double>> coords;
    for(auto &p : data["locations"]) {
        double lat = p["lat"], lon = p["lon"];
        coords.push_back({lat,lon});
        cout << "GeoHash: " << geoHash(lat,lon) << "\n";
    }

    // Build quadtree
    QuadNode* root = NULL;
    for(auto &r : data["regions"]) {
        insertQuad(root, r["x"], r["y"], r["name"]);
    }
    cout << "QuadTree Loaded!\n";

    // Graph
    int n = data["graph"]["nodes"];
    graph.assign(n, {});
    for(auto &e : data["graph"]["edges"]) {
        graph[e["u"]].push_back({e["v"], e["w"]});
    }

    auto dist = dijkstra(0);
    cout << "Shortest distance to node 3: " << dist[3] << "\n";

    // KMP search in wildlife warnings
    string keyword = data["search_keyword"];
    for(string s : data["wildlife_notes"]) {
        if(kmpSearch(s, keyword))
            cout << "Pattern found in: " << s << "\n";
    }

    cout << "Best Visit Time: " << assignTimeSlot(data["crowd_level"]) << "\n";

    return 0;
}
