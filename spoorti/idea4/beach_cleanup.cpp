#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;

struct Cell { int x, y; int cost; };

// A* pathfinding simplified
int heuristic(int x1, int y1, int x2, int y2){
    return abs(x1 - x2) + abs(y1 - y2);
}

vector<vector<int>> a_star(vector<vector<int>>& grid, Cell start, Cell goal){
    int n = grid.size(), m = grid[0].size();
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    pq.push({0, start.x, start.y});

    vector<vector<int>> dist(n, vector<int>(m, 1e9));
    dist[start.x][start.y] = 0;

    vector<vector<int>> parent(n, vector<int>(m, -1));

    int dx[4]={1,-1,0,0};
    int dy[4]={0,0,1,-1};

    while(!pq.empty()){
        auto t = pq.top(); pq.pop();
        int cost=t[0], x=t[1], y=t[2];

        if(x==goal.x && y==goal.y) break;

        for(int i=0;i<4;i++){
            int nx=x+dx[i], ny=y+dy[i];
            if(nx>=0 && ny>=0 && nx<n && ny<m && grid[nx][ny]==0){
                int newCost = cost + 1;
                if(newCost < dist[nx][ny]){
                    dist[nx][ny] = newCost;
                    pq.push({newCost + heuristic(nx,ny,goal.x,goal.y), nx, ny});
                }
            }
        }
    }
    return dist;
}

int main(){
    ifstream f("beach_data.json");
    json data;
    f >> data;

    cout << "Loaded Beach Cleanup Robot Data\n";

    vector<vector<int>> grid = data["grid"].get<vector<vector<int>>>();

    auto s = data["start"];
    auto g = data["goal"];

    Cell start{ s["x"], s["y"], 0 };
    Cell goal{ g["x"], g["y"], 0 };

    auto dist = a_star(grid, start, goal);
    cout << "Distance to goal: " << dist[goal.x][goal.y] << endl;

    return 0;
}
