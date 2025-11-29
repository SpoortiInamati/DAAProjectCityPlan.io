#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <fstream>
#include "json.hpp"
using json=nlohmann::json;
using namespace std;

struct Edge{int to; double cost;};
unordered_map<string, vector<Edge>> graphMap;

unordered_map<string,bool> boatAvailable;
unordered_map<string,string> dockStatus;

vector<string> split(const string&s){
    vector<string>res; string cur="";
    for(char c: s){ if(c==' ') {if(!cur.empty())res.push_back(cur),cur="";} else cur+=c; }
    if(!cur.empty())res.push_back(cur);
    return res;
}

unordered_map<char, unordered_map<char, double>> trie;

vector<double> fuelDP;

double getFuelOptimal(int n){
    fuelDP.assign(n+1,1e9);
    fuelDP[0]=0;
    for(int i=1;i<=n;i++){
        fuelDP[i]=min({fuelDP[i-1]+1, (i>=2?fuelDP[i-2]+1.5:1e9), (i>=3?fuelDP[i-3]+2.2:1e9)});
    }
    return fuelDP[n];
}

unordered_map<string,int> clusterId;

void loadJSON(string filename){
    ifstream f(filename);
    json data; f>>data;

    for(auto &d:data["graph"].items()){
        string dock=d.key();
        for(auto &e:d.value()){
            graphMap[dock].push_back({e["to"],e["cost"]});
        }
    }

    for(auto &b:data["boats"].items()){
        boatAvailable[b.key()]=b.value();
    }

    for(auto &d:data["dock_status"].items()){
        dockStatus[d.key()]=d.value();
    }

    int cid=0;
    for(auto &it:data["clusters"].items()){
        for(auto &x:it.value()){
            clusterId[x]=cid;
        }
        cid++;
    }
}

double dijkstraRoute(string start,string goal){
    unordered_map<string,double> dist;
    for(auto &p:graphMap) dist[p.first]=1e9;
    dist[start]=0;
    priority_queue<pair<double,string>,vector<pair<double,string>>,greater<pair<double,string>>>pq;
    pq.push({0,start});

    while(!pq.empty()){
        auto[d,u]=pq.top(); pq.pop();
        if(d>dist[u]) continue;
        if(u==goal) return d;

        for(auto &e:graphMap[u]){
            if(dist[e.to] > dist[u] + e.cost){
                dist[e.to]=dist[u]+e.cost;
                pq.push({dist[e.to], e.to});
            }
        }
    }
    return dist[goal];
}

int main(){
    loadJSON("water_taxi.json");
    cout<<"Water Taxi System Ready\n";

    string start="Karwar_Port";
    string end="Devbagh_Island";

    cout<<"Shortest marine route: "<< dijkstraRoute(start,end) <<" km\n";
    cout<<"Fuel optimized score: "<< getFuelOptimal(10) <<"\n";
    cout<<"Cluster ID for "<<start<<": "<< clusterId[start] <<"\n";

    return 0;
}
