
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>
using json = nlohmann::json;

struct RouteNode {
    std::string id;
};

int main() {
    std::ifstream f("fishery_data.json");
    if (!f.is_open()) {
        std::cerr << "Failed to open fishery_data.json\n";
        return 1;
    }

    json data;
    f >> data;

    std::cout << "Fishery Fuel Optimization System Loaded.\n";
    std::cout << "You can now process routes, fuel stats, clusters, and scheduling.\n";

    return 0;
}
